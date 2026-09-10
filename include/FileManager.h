#pragma once
#include "Contact.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class FileManager {
private:
    std::string filename;
public:
    FileManager(std::string file) : filename(std::move(file)) {}

    std::vector<Contact> loadContacts() {
        std::vector<Contact> contacts;
        std::ifstream file(filename);
        std::string line, word;

        if (!file.is_open()) return contacts;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, name, phone, email, activeStr;
            
            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, phone, ',');
            std::getline(ss, email, ',');
            std::getline(ss, activeStr, ',');

            if (!idStr.empty()) {
                Contact c(std::stoi(idStr), name, phone, email);
                c.isActive = (activeStr == "1");
                contacts.push_back(c);
            }
        }
        file.close();
        return contacts;
    }

    void saveContacts(const std::vector<Contact>& contacts) {
        std::ofstream file(filename);
        for (const auto& c : contacts) {
            // Only save active contacts to clean up file size over time
            if (c.isActive) {
                file << c.id << "," << c.name << "," << c.phone << "," << c.email << ",1\n";
            }
        }
        file.close();
    }
};