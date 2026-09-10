#pragma once
#include "Contact.h"
#include "Trie.h"
#include "UndoManager.h"
#include <vector>
#include <unordered_map>
#include <string>

class ContactManager {
private:
    std::vector<Contact> contacts;
    std::unordered_map<std::string, int> phoneIndex; // Maps phone -> vector index
    Trie nameTrie;
    UndoManager undoManager;
    int nextId;

    void rebuildIndexes();

public:
    ContactManager(std::vector<Contact> initialContacts);
    
    bool addContact(const std::string& name, const std::string& phone, const std::string& email);
    bool deleteContact(int id);
    bool updateContact(int id, const std::string& name, const std::string& phone, const std::string& email);
    void undoLastAction();
    
    // Search Methods
    Contact* searchByPhone(const std::string& phone);
    std::vector<Contact> searchByNamePrefix(const std::string& prefix);
    
    // Algorithms
    void sortContactsAlphabetically(); // Uses Merge Sort
    void mergeSort(std::vector<Contact>& arr, int left, int right);
    void merge(std::vector<Contact>& arr, int left, int mid, int right);
    
    int binarySearchExactName(const std::vector<Contact>& sortedArr, const std::string& name);

    void displayAll() const;
    std::vector<Contact> getAllContacts() const;
};