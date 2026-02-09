// Copyright 2026 Florian Favre

#ifndef INCLUDE_BIBLIOTHEQUE_HPP_
#define INCLUDE_BIBLIOTHEQUE_HPP_

#include <map>
#include <string>
#include <vector>

#include "Livre.hpp"

typedef std::map<std::string, std::vector<Livre>> Collection;

/******************************************************************************************
 * Definition of the class
 ******************************************************************************************/

class Bibliotheque {
    public:
        Bibliotheque();
        explicit Bibliotheque(std::string const& baseDeDonnees);
        ~Bibliotheque();

        void afficher() const;
        void ajouterLivre(std::string auteur, Livre livre);
        std::vector<const Livre*> rechercherParTitre(std::string const& titre) const;
        const std::vector<Livre>* rechercherParAuteur(std::string const& auteur) const;
        bool emprunterLivre(std::string auteur, std::string const& titre);
        bool retournerLivre(std::string auteur, std::string const& titre);

    private:
        Collection collection;
};

#endif  // INCLUDE_BIBLIOTHEQUE_HPP_
