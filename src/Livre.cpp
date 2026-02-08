#include <iostream>

#include "Livre.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

Livre::Livre() : titre("Titre"), auteur("Auteur"), annee(2026), disponible(1) {}

Livre::Livre(std::string titre, std::string auteur, int annee) : titre(titre), auteur(auteur), annee(annee), disponible(1) {}

Livre::Livre(std::string titre, std::string auteur, int annee, bool disponible) : titre(titre), auteur(auteur), annee(annee), disponible(disponible) {}

Livre::~Livre() {}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void Livre::afficher() const {
    std::string disp = disponible ? "disponible" : "non disponible";
    std::cout << titre << ", " << auteur << " (" << annee << "), " << disp << std::endl;
}

std::string Livre::getAuteur() const {
    return auteur;
}

std::string Livre::getTitre() const {
    return titre;
}

bool Livre::getDisponibilite() const {
    return disponible;
}

void Livre::setDisponibilite(bool dispo) {
    disponible = dispo;
}

/******************************************************************************************
 * Overloading of the operators
 ******************************************************************************************/

std::ostream& operator<<(std::ostream& os, const Livre& livre) {
    livre.afficher();
    return os;
}