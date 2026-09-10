#pragma once
#include <string>

struct Contact {
    int id;
    std::string name;
    std::string phone;
    std::string email;
    bool isActive; // Logical delete flag to simplify vector management

    Contact(int id, std::string name, std::string phone, std::string email)
        : id(id), name(std::move(name)), phone(std::move(phone)), email(std::move(email)), isActive(true) {}
    
    // Default constructor needed for some STL operations
    Contact() : id(0), isActive(false) {} 
};