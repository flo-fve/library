// Copyright 2026 Florian Favre

#ifndef INCLUDE_UTILS_HPP_
#define INCLUDE_UTILS_HPP_

#include <string>
#include <vector>

/******************************************************************************************
 * Definition of the functions
 ******************************************************************************************/

int getUserInput();

void clearScreen();

void waitForInput();

std::vector<std::string> splitString(const std::string& s, const std::string& delimiter);

std::string slugify(std::string input);

#endif  // INCLUDE_UTILS_HPP_
