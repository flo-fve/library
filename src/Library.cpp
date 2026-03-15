// Copyright 2026 Florian Favre

#include "Library.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
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

        std::string titre = "";
        std::string author = "";
        int year = 0;
        bool available = true;
        Book book;

        while (getline(flux, line)) {
            try {
                std::vector<std::string> res = splitString(line, ";");

                titre = res[0];
                author = res[1];
                year = std::stoi(res[2]);
                available = res[3] == "1";

                book = Book(titre, author, year, available);

                collection[author].push_back(book);

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
        for (auto const& it : collection) {
            auto const& books = it.second;

            for (auto const& book : books) {
                flux << book.getTitle() << ";" << book.getAuthor() << ";" << book.getYear() << ";"
                     << book.getAvailability() << "\n";
            }
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
        for (const auto& it : collection) {
            const auto& author = it.first;
            const auto& books = it.second;

            std::cout << "+ " << author << " :\n";
            for (const auto& element : books) {
                std::cout << "| " << element;
            }
        }
    }
}

int Library::numberAuthors() const {
    return collection.size();
}

int Library::numberBooks() const {
    size_t total =
        std::transform_reduce(collection.begin(), collection.end(), size_t{0}, std::plus<>(),
                              [](const auto& pair) { return pair.second.size(); });

    return total;
}

std::vector<Book> Library::getBooks() {
    std::vector<Book> books;

    for (const auto& it : collection) {
        books.insert(books.end(), it.second.begin(), it.second.end());
    }

    return books;
}

void Library::addBook(std::string const& author, Book book) {
    collection[author].push_back(book);
}

void Library::removeBook(std::string const& author, std::string const& title) {
    auto it = collection.find(author);
    if (it == collection.end()) {
        return;
    }

    auto& books = it->second;
    books.erase(std::remove_if(books.begin(), books.end(),
                               [&title](const Book& b) { return b.getTitle() == title; }),
                books.end());

    if (books.empty()) {
        collection.erase(it);
    }
}

std::vector<const Book*> Library::searchByTitle(std::string title) const {
    std::vector<const Book*> resultats;

    title = slugify(title);

    for (const auto& it : collection) {
        const auto& author = it.first;
        const auto& books = it.second;

        for (const auto& book : books) {
            std::string titleBook = book.getTitle();

            titleBook = slugify(titleBook);

            if (titleBook == title) {
                resultats.push_back(&book);
            }
        }
    }

    return resultats;
}

const std::vector<Book>* Library::searchByAuthor(std::string const& author) const {
    auto it = collection.find(author);

    if (it == collection.end()) {
        throw std::string("Author not found");
    }

    return &it->second;
}

bool Library::borrowBook(std::string author, std::string const& titre) {
    if (!collection[author].empty()) {
        auto& books = collection[author];

        auto it = std::ranges::find_if(
            books, [&](const Book& l) { return l.getTitle() == titre && l.getAvailability(); });

        if (it != books.end()) {
            it->setAvailability(false);
            return true;
        }
    }

    return false;
}

bool Library::returnBook(std::string author, std::string const& titre) {
    auto book = std::find_if(collection[author].begin(), collection[author].end(),
                             [&](const Book& obj) { return obj.getTitle() == titre; });

    if (book != collection[author].end()) {
        book->setAvailability(true);
        return true;
    }

    return false;
}
