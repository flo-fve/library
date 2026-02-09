// Copyright 2026 Florian Favre

#include "utils.hpp"

#include <iostream>
#include <string>
#include <vector>

/******************************************************************************************
 * Functions
 ******************************************************************************************/

void afficherMenu() {
    std::cout << "1. Ajouter un livre" << std::endl;
    std::cout << "2. Rechercher un livre" << std::endl;
    std::cout << "3. Afficher les livres" << std::endl;
    std::cout << "4. Emprunter un livre" << std::endl;
    std::cout << "5. Retourner un livre" << std::endl;
    std::cout << "6. Quitter" << std::endl;
}

std::vector<std::string> diviserChaine(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0;
    size_t pos_end;
    size_t delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}
