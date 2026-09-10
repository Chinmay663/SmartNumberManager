#pragma once
#include <string>
#include <regex>

class Validator {
public:
    static bool isValidName(const std::string& name) {
        return !name.empty();
    }

    static bool isValidPhone(const std::string& phone) {
        // Simple 10-digit validation for fresher level
        std::regex phonePattern("^[0-9]{10}$");
        return std::regex_match(phone, phonePattern);
    }

    static bool isValidEmail(const std::string& email) {
        std::regex emailPattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
        return std::regex_match(email, emailPattern);
    }
};