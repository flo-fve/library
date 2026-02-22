// Copyright 2026 Florian Favre

#include "utils.hpp"

#include <iostream>
#include <string>
#include <vector>

/******************************************************************************************
 * Functions
 ******************************************************************************************/

void displayMenu() {
    std::cout << "1. Add a book\n";
    std::cout << "2. Search for a book\n";
    std::cout << "3. Display the books\n";
    std::cout << "4. Borrow a book\n";
    std::cout << "5. Return a book\n";
    std::cout << "6. Exit\n";
}

std::vector<std::string> splitString(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0;
    size_t pos_end;
    size_t delim_len = delimiter.length();
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        const std::string token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}
