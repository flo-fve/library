// Copyright 2026 Florian Favre

#include <iostream>
#include <vector>

#include "Book.hpp"
#include "Library.hpp"
#include "utils.hpp"

using namespace std;

/******************************************************************************************
 * Main
 ******************************************************************************************/

int main(int argc, const char* argv[]) {
    string data;

    if (argc == 2) {
        data = argv[1];
    } else {
        data = "";
    }

    Library library(data);

    int action = 0;

    while (action != 6) {
        displayMenu();

        cout << "Select the action: ";
        cin >> action;
        cin.ignore();

        if (action == 1) {  // Add a book
            Book book;
            string title = "Title";
            string author = "Author";
            int year = 0;

            cout << "  Title: ";
            getline(cin, title);

            cout << "  Author: ";
            getline(cin, author);

            cout << "  Year: ";
            cin >> year;
            cin.ignore();

            book = Book(title, author, year);

            library.addBook(author, book);

        } else if (action == 2) {  // Search for a book
            int searchType = 0;

            while (searchType != 1 && searchType != 2) {
                cout << "  1. Search by title\n";
                cout << "  2. Search by author\n";
                cout << "  3. Back to the menu\n";

                cout << "  Choice: ";
                cin >> searchType;
                cin.ignore();

                if (searchType == 1) {  // By title
                    string titleSearched;

                    cout << "Title: ";
                    getline(cin, titleSearched);

                    vector<const Book*> resultats = library.searchByTitle(titleSearched);

                    if (!resultats.empty()) {
                        for (const auto& book : resultats) {
                            book->display();
                        }
                    } else {
                        cout << "Title not found\n";
                    }

                } else if (searchType == 2) {  // By author
                    string authorSearched;

                    cout << "Author: ";
                    getline(cin, authorSearched);

                    try {
                        const vector<Book>* authorBiblio = library.searchByAuthor(authorSearched);

                        for (const auto& book : *authorBiblio) {
                            book.display();
                        }
                    } catch (string const& erreur) {
                        cerr << erreur << "\n";
                    }

                } else if (searchType == 3) {  // Back to the menu
                    break;

                } else {
                    cout << "Incorrect choice\n";
                }
            }

        } else if (action == 3) {  // Display available books
            library.display();

        } else if (action == 4) {  // Borrow a book
            string titleEmprunt = "";
            string authorEmprunt = "";

            cout << "  Title: ";
            getline(cin, titleEmprunt);

            cout << "  Author: ";
            getline(cin, authorEmprunt);

            if (library.borrowBook(authorEmprunt, titleEmprunt)) {
                cout << "Book '" << titleEmprunt << "' borrowed\n";
            } else {
                cout << "Book not found\n";
            }

        } else if (action == 5) {  // Return a book
            string titleRetourne = "";
            string authorRetourne = "";

            cout << "  Title: ";
            getline(cin, titleRetourne);

            cout << "  Author: ";
            getline(cin, authorRetourne);

            if (library.returnBook(authorRetourne, titleRetourne)) {
                cout << "Book '" << titleRetourne << "' returned\n";
            } else {
                cout << "Book not found\n";
            }

        } else if (action == 6) {  // Exit
            return 0;

        } else {
            cout << "Incorrect choice\n";
        }
    }

    return 0;
}
