#include "ContactManager.h"
#include "Validator.h"
#include <iostream>
#include <algorithm>

ContactManager::ContactManager(std::vector<Contact> initialContacts) : contacts(std::move(initialContacts)) {
    nextId = contacts.empty() ? 1 : contacts.back().id + 1;
    rebuildIndexes();
}

void ContactManager::rebuildIndexes() {
    phoneIndex.clear();
    nameTrie = Trie(); // Reset Trie
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].isActive) {
            phoneIndex[contacts[i].phone] = i;
            nameTrie.insert(contacts[i].name, i);
        }
    }
}

bool ContactManager::addContact(const std::string& name, const std::string& phone, const std::string& email) {
    if (phoneIndex.find(phone) != phoneIndex.end()) return false; // Duplicate phone

    Contact newContact(nextId++, name, phone, email);
    contacts.push_back(newContact);
    
    undoManager.recordAction(ActionType::ADD, newContact);
    rebuildIndexes();
    return true;
}

bool ContactManager::deleteContact(int id) {
    for (auto& c : contacts) {
        if (c.id == id && c.isActive) {
            undoManager.recordAction(ActionType::DELETE, c); // Save state before delete
            c.isActive = false; // Logical delete
            rebuildIndexes();
            return true;
        }
    }
    return false;
}

void ContactManager::undoLastAction() {
    if (!undoManager.hasActions()) return;
    
    UndoAction action = undoManager.popAction();
    
    // Find the contact in our vector
    for (auto& c : contacts) {
        if (c.id == action.contactState.id) {
            if (action.type == ActionType::ADD) {
                c.isActive = false; // Undo Add = Delete
            } else if (action.type == ActionType::DELETE) {
                c.isActive = true;  // Undo Delete = Restore
            }
            break;
        }
    }
    rebuildIndexes();
}

Contact* ContactManager::searchByPhone(const std::string& phone) {
    if (phoneIndex.find(phone) != phoneIndex.end()) {
        return &contacts[phoneIndex[phone]];
    }
    return nullptr;
}

std::vector<Contact> ContactManager::searchByNamePrefix(const std::string& prefix) {
    std::vector<Contact> results;
    std::vector<int> indices = nameTrie.searchPrefix(prefix);
    for (int idx : indices) {
        results.push_back(contacts[idx]);
    }
    return results;
}


void ContactManager::merge(std::vector<Contact>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Contact> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].name <= R[j].name) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void ContactManager::mergeSort(std::vector<Contact>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void ContactManager::sortContactsAlphabetically() {
    std::vector<Contact> activeContacts;
    for (const auto& c : contacts) if (c.isActive) activeContacts.push_back(c);
    
    if (!activeContacts.empty()) {
        mergeSort(activeContacts, 0, activeContacts.size() - 1);
    }
    
    std::cout << "\nSorted Contacts:\n";
    for (const auto& c : activeContacts) {
        std::cout << "ID: " << c.id << " | Name: " << c.name << " | Phone: " << c.phone << "\n";
    }
}

int ContactManager::binarySearchExactName(const std::vector<Contact>& sortedArr, const std::string& name) {
    int left = 0, right = sortedArr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sortedArr[mid].name == name) return sortedArr[mid].id;
        if (sortedArr[mid].name < name) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

std::vector<Contact> ContactManager::getAllContacts() const { return contacts; }