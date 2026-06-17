// Copyright 2026 Florian Favre

#include "Library.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Book.hpp"
#include "utils.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

Library::Library() {}

Library::Library(std::string const& data) {
    std::ifstream flux(data.c_str());

    save = data;

    if (flux) {
        std::string line;

        std::string title = "";
        std::string author = "";
        int year = 0;
        bool available = true;
        Book book;

        while (getline(flux, line)) {
            try {
                std::vector<std::string> res = splitString(line, ";");

                author = res[0];
                title = res[1];
                year = std::stoi(res[2]);
                available = res[3] == "1";

                book = Book(title, author, year, available);

                collection.push_back(book);

            } catch (std::exception const& e) {
                std::cerr << "The library could not be loaded (error reading): " << e.what()
                          << ")\n";

                break;
            }
        }
    } else {
        std::cerr << "The library could not be loaded (error file)\n";
    }
}

Library::~Library() {
    std::ofstream flux(save.c_str());

    if (flux) {
        std::stable_sort(collection.begin(), collection.end(), [](const Book& b1, const Book& b2) {
            return b1.getAuthor() < b2.getAuthor();
        });

        for (auto const& book : collection) {
            flux << book.getAuthor() << ";" << book.getTitle() << ";" << book.getYear() << ";"
                 << book.getAvailability() << "\n";
        }
    } else {
        std::cerr << "The library could not be saved (error file)\n";
    }
}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void Library::display() const {
    if (!collection.size()) {
        std::cout << "There are no book in the library\n";

    } else {
        for (const auto& book : collection) {
            std::cout << "| ";
            book.display();
        }
    }
}

int Library::numberAuthors() const {
    std::set<std::string> uniqueAuthors;

    for (const auto& book : collection) {
        uniqueAuthors.insert(book.getAuthor());
    }

    return uniqueAuthors.size();
}

int Library::numberBooks() const {
    return collection.size();
}

std::vector<Book> Library::getBooks() {
    return collection;
}

void Library::addBook(Book book) {
    collection.push_back(book);
}

bool Library::removeBook(std::string const& author, std::string const& title) {
    auto it =
        std::remove_if(collection.begin(), collection.end(), [&title, &author](const Book& b) {
            return b.getTitle() == title && b.getAuthor() == author;
        });

    bool found = (it != collection.end());

    collection.erase(it, collection.end());

    return found;
}

bool Library::borrowBook(std::string const& author, std::string const& title) {
    auto it = std::find_if(collection.begin(), collection.end(), [&title, &author](const Book& b) {
        return equalsIgnoreCase(b.getTitle(), title) && equalsIgnoreCase(b.getAuthor(), author);
    });

    if (it == collection.end()) {
        return false;
    }

    Book book = *it;
    book.setAvailability(false);

    return true;
}

bool Library::returnBook(std::string const& author, std::string const& title) {
    auto it = std::find_if(collection.begin(), collection.end(), [&title, &author](const Book& b) {
        return equalsIgnoreCase(b.getTitle(), title) && equalsIgnoreCase(b.getAuthor(), author);
    });

    if (it == collection.end()) {
        return false;
    }

    Book book = *it;
    book.setAvailability(true);

    return true;
}

std::vector<Book> Library::searchByTitle(std::string const& title) const {
    std::vector<Book> result;

    std::copy_if(collection.begin(), collection.end(), std::back_inserter(result),
                 [&title](const Book& b) { return equalsIgnoreCase(b.getTitle(), title); });

    return result;
}

std::vector<Book> Library::searchByAuthor(std::string const& author) const {
    std::vector<Book> result;

    std::copy_if(collection.begin(), collection.end(), std::back_inserter(result),
                 [&author](const Book& b) { return equalsIgnoreCase(b.getAuthor(), author); });

    return result;
}
