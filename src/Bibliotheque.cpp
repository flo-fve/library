// Copyright 2026 Florian Favre

#include "Bibliotheque.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Livre.hpp"
#include "utils.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

Bibliotheque::Bibliotheque() {}

Bibliotheque::Bibliotheque(std::string const& BaseDeDonnees) {
    std::ifstream flux(BaseDeDonnees.c_str());

    if (flux) {
        std::string ligne;

        std::string titre = "";
        std::string auteur = "";
        int annee = 0;
        bool disponible = true;
        Livre livre;

        while (getline(flux, ligne)) {
            try {
                std::vector<std::string> res = diviserChaine(ligne, ";");

                titre = res[0];
                auteur = res[1];
                annee = std::stoi(res[2]);
                disponible = res[3] == "vrai";

                livre = Livre(titre, auteur, annee, disponible);

                collection[auteur].push_back(livre);

            } catch (std::exception const& e) {
                std::cerr << "La bibliothèque n'a pas pu être chargée (erreur lecture : "
                          << e.what() << ")\n";

                break;
            }
        }
    } else {
        std::cerr << "La bibliothèque n'a pas pu être chargée (erreur fichier)\n";
    }
}

Bibliotheque::~Bibliotheque() {}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void Bibliotheque::afficher() const {
    if (!collection.size()) {
        std::cout << "Il n'y a aucun livre dans la bibliothèque\n";

    } else {
        for (const auto& it : collection) {
            const auto& auteur = it.first;
            const auto& livres = it.second;

            std::cout << "+ " << auteur << " :\n";
            for (const auto& element : livres) {
                std::cout << "| " << element;
            }
        }
    }
}

void Bibliotheque::ajouterLivre(std::string auteur, Livre livre) {
    collection[auteur].push_back(livre);
}

std::vector<const Livre*> Bibliotheque::rechercherParTitre(std::string const& titre) const {
    std::vector<const Livre*> resultats;

    for (const auto& it : collection) {
        const auto& auteur = it.first;
        const auto& livres = it.second;

        for (const auto& livre : livres) {
            if (livre.getTitre() == titre) {
                resultats.push_back(&livre);
            }
        }
    }

    return resultats;
}

const std::vector<Livre>* Bibliotheque::rechercherParAuteur(std::string const& auteur) const {
    auto it = collection.find(auteur);

    if (it == collection.end()) {
        throw std::string("Auteur non trouvé");
    }

    return &it->second;
}

bool Bibliotheque::emprunterLivre(std::string auteur, std::string const& titre) {
    if (!collection[auteur].empty()) {
        auto& livres = collection[auteur];

        auto it = std::ranges::find_if(
            livres, [&](const Livre& l) { return l.getTitre() == titre && l.getDisponibilite(); });

        if (it != livres.end()) {
            it->setDisponibilite(false);
            return true;
        }
    }

    return false;
}

bool Bibliotheque::retournerLivre(std::string auteur, std::string const& titre) {
    auto livre = std::find_if(collection[auteur].begin(), collection[auteur].end(),
                              [&](const Livre& obj) { return obj.getTitre() == titre; });

    if (livre != collection[auteur].end()) {
        livre->setDisponibilite(true);
        return true;
    }

    return false;
}
