#ifndef BIBLIOTHEQUE_HPP
#define BIBLIOTHEQUE_HPP

#include <string>
#include <map>
#include <vector>

#include "Livre.hpp"

typedef std::map<std::string, std::vector<Livre>> Collection;

/******************************************************************************************
 * Definition of the class
 ******************************************************************************************/

class Bibliotheque {
    public:
        Bibliotheque();
        ~Bibliotheque();

        void afficher() const;
        void ajouterLivre(std::string auteur, Livre livre);
        std::vector<const Livre*> rechercherParTitre(std::string titre) const;
        const std::vector<Livre>* rechercherParAuteur(std::string auteur) const;
        bool emprunterLivre(std::string auteur, std::string titre);
        bool retournerLivre(std::string auteur, std::string titre);

    private:
        Collection collection;
};

#endif