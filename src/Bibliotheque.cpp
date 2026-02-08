#include <algorithm>
#include <iostream>
#include <vector>

#include "Bibliotheque.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

Bibliotheque::Bibliotheque() {}

Bibliotheque::~Bibliotheque() {}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void Bibliotheque::afficher() const {
    if (!collection.size()) {
        std::cout << "Il n'y a aucun livre dans la bibliothèque" << std::endl;

    } else {
        std::map<std::string, std::vector<Livre>>::const_iterator it;

        for (const auto& [auteur, vecteur] : collection) {
            std::cout << "+ " << auteur << " :" << std::endl;
            for (const auto& element : vecteur) {
                std::cout << "| " << element;
            }
        }
    }
}

void Bibliotheque::ajouterLivre(std::string auteur, Livre livre) {
    collection[auteur].push_back(livre);
}

std::vector<const Livre*> Bibliotheque::rechercherParTitre(std::string titre) const {
    std::vector<const Livre*> resultats;

    for (const auto& [auteur, livres] : collection) {
        for (const auto& livre : livres) {
            if (livre.getTitre() == titre) {
                resultats.push_back(&livre);
            }
        }
    }

    return resultats;
}

const std::vector<Livre>* Bibliotheque::rechercherParAuteur(std::string auteur) const {
    auto it = collection.find(auteur);

    if (it == collection.end()) {
        throw std::string("Auteur non trouvé");
    }
        
    return &it->second;
}

bool Bibliotheque::emprunterLivre(std::string auteur, std::string titre) {
    if (!collection[auteur].empty()) {
        for (auto& livre : collection[auteur]) {
            if (livre.getTitre() == titre && livre.getDisponibilite()) {             
                livre.setDisponibilite(false);

                return true;
            }
        }
    }
    
    return false;
}

bool Bibliotheque::retournerLivre(std::string auteur, std::string titre) {
    auto livre = std::find_if(
        collection[auteur].begin(),
        collection[auteur].end(),
        [&](const Livre& obj) {
            return obj.getTitre() == titre;
        }
    );

    if (livre != collection[auteur].end()) {
        livre->setDisponibilite(true);
        return true;
    }

    return false;
}