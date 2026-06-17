// Copyright 2026 Florian Favre

#ifndef INCLUDE_BIBLIOTHEQUE_HPP_
#define INCLUDE_BIBLIOTHEQUE_HPP_

#include <map>
#include <string>
#include <vector>

#include "Book.hpp"

typedef std::vector<Book> Collection;

/******************************************************************************************
 * Definition of the class
 ******************************************************************************************/

class Library {
    public:
        Library();
        explicit Library(std::string const& data);
        ~Library();

        void display() const;

        std::vector<Book> getBooks();
        int numberAuthors() const;
        int numberBooks() const;

        void addBook(Book book);
        bool removeBook(std::string const& author, std::string const& title);
        bool borrowBook(std::string const& author, std::string const& title);
        bool returnBook(std::string const& author, std::string const& title);
        std::vector<Book> searchByTitle(std::string const& title) const;
        std::vector<Book> searchByAuthor(std::string const& author) const;

    private:
        Collection collection;
        std::string save;
};

#endif  // INCLUDE_BIBLIOTHEQUE_HPP_
