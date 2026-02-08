#ifndef LIVRE_HPP
#define LIVRE_HPP

#include <string>
#include <vector>

/******************************************************************************************
 * Definition of the class
 ******************************************************************************************/

class Livre {
    public:
        Livre();
        Livre(std::string titre, std::string auteur, int annee);
        Livre(std::string titre, std::string auteur, int annee, bool disponible);
        ~Livre();

        void afficher() const;
        
        std::string getAuteur() const;
        std::string getTitre() const;
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

#endif