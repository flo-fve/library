// Copyright 2026 Florian Favre

#ifndef INCLUDE_LIVRE_HPP_
#define INCLUDE_LIVRE_HPP_

#include <string>
#include <vector>

/******************************************************************************************
 * Definition of the class
 ******************************************************************************************/

class Livre {
    public:
        Livre();
        Livre(std::string const& titre, std::string const& auteur, int annee);
        Livre(std::string const& titre, std::string const& auteur, int annee, bool disponible);
        ~Livre();

        void afficher() const;

        std::string getAuteur() const;
        std::string getTitre() const;
        int getAnnee() const;
        bool getDisponibilite() const;

        void setDisponibilite(bool dispo);

    private:
        std::string titre;
        std::string auteur;
        int annee;
        bool disponible;
};

/******************************************************************************************
 * Overloading of the operators
 ******************************************************************************************/

std::ostream& operator<<(std::ostream& os, const Livre& livre);

#endif  // INCLUDE_LIVRE_HPP_
