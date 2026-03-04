// Copyright 2026 Florian Favre

#ifndef INCLUDE_UTILS_HPP_
#define INCLUDE_UTILS_HPP_

#include <string>
#include <vector>

/******************************************************************************************
 * Definition of the functions
 ******************************************************************************************/

void displayMenu();

std::vector<std::string> splitString(const std::string& s, const std::string& delimiter);

std::string slugify(std::string input);

#endif  // INCLUDE_UTILS_HPP_
