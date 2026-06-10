// Copyright 2026 Florian Favre

#include "utils.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

/******************************************************************************************
 * Colors
 ******************************************************************************************/

namespace Color {
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
}  // namespace Color

/******************************************************************************************
 * Functions
 ******************************************************************************************/

int getUserInput() {
    int choice;
    std::cout << "Choice: ";

    while (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << Color::RED << "Invalid input. Please try again: " << Color::RESET;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return choice;
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

std::string slugify(std::string input) {
    static const std::unordered_map<std::string, std::string> accents = {
        {"à", "a"}, {"á", "a"}, {"â", "a"}, {"ä", "a"}, {"À", "a"}, {"Á", "a"}, {"Â", "a"},
        {"Ä", "a"}, {"è", "e"}, {"é", "e"}, {"ê", "e"}, {"ë", "e"}, {"È", "e"}, {"É", "e"},
        {"Ê", "e"}, {"Ë", "e"}, {"ì", "i"}, {"í", "i"}, {"î", "i"}, {"ï", "i"}, {"Ì", "i"},
        {"Í", "i"}, {"Î", "i"}, {"Ï", "i"}, {"ò", "o"}, {"ó", "o"}, {"ô", "o"}, {"ö", "o"},
        {"Ò", "o"}, {"Ó", "o"}, {"Ô", "o"}, {"Ö", "o"}, {"ù", "u"}, {"ú", "u"}, {"û", "u"},
        {"ü", "u"}, {"Ù", "u"}, {"Ú", "u"}, {"Û", "u"}, {"Ü", "u"}, {"ç", "c"}, {"Ç", "c"},
        {"ñ", "n"}, {"Ñ", "n"}};

    std::string result;

    for (size_t i = 0; i < input.size();) {
        unsigned char c = input[i];
        size_t len = 1;

        if ((c & 0xE0) == 0xC0) {
            len = 2;
        } else if ((c & 0xF0) == 0xE0) {
            len = 3;
        } else if ((c & 0xF8) == 0xF0) {
            len = 4;
        }

        std::string ch = input.substr(i, len);

        if (accents.contains(ch))
            result += accents.at(ch);
        else
            result += ch;

        i += len;
    }

    input = result;

    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    input = std::regex_replace(input, std::regex("[^a-z0-9\\s-]"), "");

    input = std::regex_replace(input, std::regex("\\s+"), "-");

    input = std::regex_replace(input, std::regex("-+"), "-");

    input = std::regex_replace(input, std::regex("^-|-$"), "");

    return input;
}
