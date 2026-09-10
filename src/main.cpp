#include "ContactManager.h"
#include "FileManager.h"
#include "Validator.h"
#include <iostream>

void displayMenu() {
    std::cout << "\n=== SMART CONTACT MANAGER ===\n";
    std::cout << "1. Add Contact\n";
    std::cout << "2. Search by Phone (O(1))\n";
    std::cout << "3. Prefix Name Search (Trie)\n";
    std::cout << "4. Delete Contact\n";
    std::cout << "5. Undo Last Action\n";
    std::cout << "6. Sort Alphabetically (Merge Sort)\n";
    std::cout << "7. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    FileManager fm("data/contacts.csv");
    ContactManager manager(fm.loadContacts());

    int choice;
    while (true) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name, phone, email;
            std::cout << "Name: "; std::cin >> name;
            std::cout << "Phone (10 digits): "; std::cin >> phone;
            std::cout << "Email: "; std::cin >> email;

            if (Validator::isValidPhone(phone) && Validator::isValidEmail(email)) {
                if (manager.addContact(name, phone, email)) std::cout << "Added successfully!\n";
                else std::cout << "Error: Phone number already exists.\n";
            } else {
                std::cout << "Invalid phone or email format.\n";
            }
        } 
        else if (choice == 2) {
            std::string phone;
            std::cout << "Enter Phone: "; std::cin >> phone;
            Contact* c = manager.searchByPhone(phone);
            if (c) std::cout << "Found: " << c->name << " (" << c->email << ")\n";
            else std::cout << "Not found.\n";
        }
        else if (choice == 3) {
            std::string prefix;
            std::cout << "Enter name prefix: "; std::cin >> prefix;
            auto results = manager.searchByNamePrefix(prefix);
            std::cout << "Found " << results.size() << " matches.\n";
            for (const auto& c : results) std::cout << "- " << c.name << "\n";
        }
        else if (choice == 4) {
            int id;
            std::cout << "Enter Contact ID to delete: "; std::cin >> id;
            if (manager.deleteContact(id)) std::cout << "Deleted.\n";
            else std::cout << "ID not found.\n";
        }
        else if (choice == 5) {
            manager.undoLastAction();
            std::cout << "Undo executed.\n";
        }
        else if (choice == 6) {
            manager.sortContactsAlphabetically();
        }
        else if (choice == 7) {
            fm.saveContacts(manager.getAllContacts());
            std::cout << "Contacts saved. Exiting...\n";
            break;
        }
    }
    return 0;
}