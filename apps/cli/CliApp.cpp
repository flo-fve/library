#include "CliApp.hpp"

#include <iostream>
#include <vector>

#include "../../include/utils.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

CliApp::CliApp(Library& library) : library(library), currentState(MenuState::Main) {}

CliApp::~CliApp() {}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

int CliApp::displayMenuMain() {
    std::cout << "\n================================\n"
              << "MAIN\n"
              << "================================\n"
              << "[1] Books menu\n"
              //   << "[2] Members menu\n"
              << "--------------------------------\n"
              << "[0] Exit\n"
              << "================================\n";

    int choice = getUserInput();
    return choice;
}

int CliApp::displaySubMenuBooks() {
    std::cout << "\n================================\n"
              << "MAIN > BOOKS MANAGEMENT\n"
              << "================================\n"
              << "[1] Display the books (" << library.numberBooks() << ")\n"
              << "[2] Search for a book\n"
              << "[3] Borrow a book\n"
              << "[4] Return a book\n"
              << "[5] Add a book\n"
              << "[6] Remove a book\n"
              << " -------------------------------\n"
              << "[0] Back\n"
              << "================================\n";

    int choice = getUserInput();
    return choice;
}

int CliApp::displaySubSubMenuSearch() {
    std::cout << "\n================================\n"
              << "MAIN > BOOKS MANAGEMENT > SEARCH\n"
              << "================================\n"
              << "[1] Search by title\n"
              << "[2] Search by author\n"
              << " -------------------------------\n"
              << "[0] Back\n"
              << "================================\n";

    int choice = getUserInput();
    return choice;
}

void CliApp::execute() {
    while (currentState != MenuState::Exit) {
        switch (currentState) {
            case MenuState::Main: {
                int choice = displayMenuMain();

                if (choice == 1) {
                    currentState = MenuState::BooksManagement;
                } else if (choice == 0) {
                    currentState = MenuState::Exit;
                } else {
                    std::cout << "Invalid input. Please try again.\n";
                }
                break;
            }

            case MenuState::BooksManagement: {
                int choice = displaySubMenuBooks();

                if (choice == 1) {
                    library.display();
                } else if (choice == 2) {
                    currentState = MenuState::BookSearch;
                } else if (choice == 3) {
                    currentState = MenuState::BookBorrow;
                } else if (choice == 4) {
                    currentState = MenuState::BookReturn;
                } else if (choice == 5) {
                    currentState = MenuState::BookAdd;
                } else if (choice == 6) {
                    currentState = MenuState::BookRemove;
                } else if (choice == 0) {
                    currentState = MenuState::Main;
                } else {
                    std::cout << "Invalid input. Please try again.\n";
                }
                break;
            }

            case MenuState::BookSearch: {
                int choice = displaySubSubMenuSearch();

                if (choice == 1) {
                    std::string titleSearched;

                    std::cout << "Title: ";
                    std::getline(std::cin, titleSearched);

                    std::vector<const Book*> resultats = library.searchByTitle(titleSearched);

                    if (!resultats.empty()) {
                        for (const auto& book : resultats) {
                            std::cout << "+ ";
                            book->display();
                        }
                    } else {
                        std::cout << "+ Title not found\n";
                    }
                } else if (choice == 2) {
                    std::string authorSearched;

                    std::cout << "Author: ";
                    std::getline(std::cin, authorSearched);

                    try {
                        const std::vector<Book>* authorBiblio =
                            library.searchByAuthor(authorSearched);

                        for (const auto& book : *authorBiblio) {
                            std::cout << "+ ";
                            book.display();
                        }
                    } catch (std::string const& error) {
                        std::cerr << "  " << error << "\n";
                    }
                } else if (choice == 0) {
                    currentState = MenuState::BooksManagement;
                }
                break;
            }

            case MenuState::BookBorrow: {
                std::string titleBorrowed = "";
                std::string authorBorrowed = "";

                std::cout << "Title: ";
                std::getline(std::cin, titleBorrowed);

                std::cout << "Author: ";
                std::getline(std::cin, authorBorrowed);

                if (library.borrowBook(authorBorrowed, titleBorrowed)) {
                    std::cout << "+ Book '" << titleBorrowed << "' borrowed\n";

                    currentState = MenuState::BooksManagement;
                } else {
                    std::cout << "+ Book not found\n";
                }
                break;
            }

            case MenuState::BookReturn: {
                std::string titleReturned = "";
                std::string authorReturned = "";

                std::cout << "Title: ";
                std::getline(std::cin, titleReturned);

                std::cout << "Author: ";
                std::getline(std::cin, authorReturned);

                if (library.returnBook(authorReturned, titleReturned)) {
                    std::cout << "+ Book '" << titleReturned << "' returned\n";

                    currentState = MenuState::BooksManagement;
                } else {
                    std::cout << "+ Book not found\n";
                }
                break;
            }

            case MenuState::BookAdd: {
                Book book;
                std::string title = "Title";
                std::string author = "Author";
                int year = 0;

                std::cout << "Title: ";
                std::getline(std::cin, title);

                std::cout << "Author: ";
                std::getline(std::cin, author);

                std::cout << "Year: ";
                std::cin >> year;
                std::cin.ignore();

                book = Book(title, author, year);

                library.addBook(author, book);

                currentState = MenuState::BooksManagement;
                break;
            }

            case MenuState::BookRemove: {
                std::string title = "Title";
                std::string author = "Author";

                std::cout << "Title: ";
                std::getline(std::cin, title);

                std::cout << "Author: ";
                std::getline(std::cin, author);

                library.removeBook(author, title);

                currentState = MenuState::BooksManagement;
                break;
            }

            case MenuState::Exit: {
                break;
            }

            default:
                break;
        }
    }
}
