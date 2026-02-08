#include <iostream>
#include <vector>

#include "Bibliotheque.hpp"
#include "Livre.hpp"
#include "utils.hpp"

using namespace std;

/******************************************************************************************
 * Main
 ******************************************************************************************/

int main(int argc, const char *argv[]) {
    // Bibliotheque
    Bibliotheque biblio("data/livres.txt");

    // Affichage du menu
    afficherMenu();
    
    // Choix de l'action
    int action = 0;

    while (action != 6) {
        cout << endl << "Choisir l'action : ";
        cin >> action;
        cin.ignore();
        
        // Action
        if (action == 1) { // Ajouter un livre
            Livre livre;
            string titre = "Titre";
            string auteur = "Auteur";
            int annee = 0;

            cout << "  Titre : ";
            getline(cin, titre);

            cout << "  Auteur : ";
            getline(cin, auteur);

            cout << "  Année : ";
            cin >> annee;
            cin.ignore();

            livre = Livre(titre, auteur, annee);

            biblio.ajouterLivre(auteur, livre);

        } else if (action == 2) { // Rechercher un livre
            int typeRecherche = 0;

            while (typeRecherche != 1 && typeRecherche != 2) {
                cout << "  1. Rechercher par titre" << endl;
                cout << "  2. Rechercher par auteur" << endl;
                cout << "  3. Revenir au menu" << endl;
    
                cin >> typeRecherche;
                cin.ignore();

                if (typeRecherche == 1) { // Recherche par titre
                    string titreRecherche;
                    
                    cout << "Titre : ";
                    getline(cin, titreRecherche);

                    vector<const Livre*> resultats = biblio.rechercherParTitre(titreRecherche);

                    if (!resultats.empty()) {
                        for (const auto& livre : resultats) {
                            livre->afficher();
                        }
                    } else {
                        cout << "Titre non trouvé" << endl;
                    }
                    
                } else if (typeRecherche == 2) { // Recherche par auteur
                    string auteurRecherche;
                    
                    cout << "Auteur : ";
                    getline(cin, auteurRecherche);

                    try {
                        const vector<Livre>* auteurBiblio = biblio.rechercherParAuteur(auteurRecherche);

                        for (const auto& livre : *auteurBiblio) {
                            livre.afficher();
                        }
                    } catch (string const& erreur) {
                        cerr << erreur << endl;
                    }
                    
                } else if (typeRecherche == 3) {  // Revenir au menu
                    break;

                } else {
                    cout << "Choix non reconnu" << endl;
                }
            }

        } else if (action == 3) { // Afficher les livres disponibles
            biblio.afficher();

        } else if (action == 4) { // Emprunter un livre
            string titreEmprunt = "";
            string auteurEmprunt = "";

            cout << "  Titre : ";
            getline(cin, titreEmprunt);

            cout << "  Auteur : ";
            getline(cin, auteurEmprunt);
            
            if (biblio.emprunterLivre(auteurEmprunt, titreEmprunt)) {
                cout << "Livre '" << titreEmprunt << "' emprunté" << endl;
            } else {   
                cout << "Livre non trouvé" << endl;
            }

        } else if (action == 5) { // Retourner un livre
            string titreRetourne = "";
            string auteurRetourne = "";

            cout << "  Titre : ";
            getline(cin, titreRetourne);

            cout << "  Auteur : ";
            getline(cin, auteurRetourne);

            if (biblio.retournerLivre(auteurRetourne, titreRetourne)) {
                cout << "Livre '" << titreRetourne << "' retourné" << endl;
            } else {   
                cout << "Livre non trouvé" << endl;
            }

        } else if (action == 6) { // Quitter
            exit(0);

        } else {
            cout << "Choix non reconnu" << endl;
        }
    }

    return 0;
}