#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Bibliotheque.hpp"
#include "Livre.hpp"
#include "utils.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

Bibliotheque::Bibliotheque() {}

Bibliotheque::Bibliotheque(std::string BaseDeDonnees) {
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
                std::cerr << "La bibliothèque n'a pas pu être chargée (erreur lecture : " << e.what() << ")" << std::endl; 
                
                break;
            }
        }
    } else {
        std::cerr << "La bibliothèque n'a pas pu être chargée (erreur fichier)" << std::endl;

    }
}

Bibliotheque::~Bibliotheque() {}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void Bibliotheque::afficher() const {
    if (!collection.size()) {
        std::cout << "Il n'y a aucun livre dans la bibliothèque" << std::endl;

    } else {
        Collection::const_iterator it;

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