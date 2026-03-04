// Copyright 2026 Florian Favre

#ifndef INCLUDE_BIBLIOTHEQUE_HPP_
#define INCLUDE_BIBLIOTHEQUE_HPP_

#include <map>
#include <string>
#include <vector>

#include "Book.hpp"

typedef std::map<std::string, std::vector<Book>> Collection;

/******************************************************************************************
 * Definition of the class
 ******************************************************************************************/

class Library {
    public:
        Library();
        explicit Library(std::string const& data);
        ~Library();

        void display() const;
        void addBook(std::string const& author, Book book);
        std::vector<const Book*> searchByTitle(std::string title) const;
        const std::vector<Book>* searchByAuthor(std::string const& author) const;
        bool borrowBook(std::string author, std::string const& title);
        bool returnBook(std::string author, std::string const& title);

    private:
        Collection collection;
        std::string save;
};

#endif  // INCLUDE_BIBLIOTHEQUE_HPP_
