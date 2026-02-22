// Copyright 2026 Florian Favre

#ifndef INCLUDE_LIVRE_HPP_
#define INCLUDE_LIVRE_HPP_

#include <string>
#include <vector>

/******************************************************************************************
 * Definition of the class
 ******************************************************************************************/

class Book {
    public:
        Book();
        Book(std::string const& title, std::string const& author, int year);
        Book(std::string const& title, std::string const& author, int year, bool available);
        ~Book();

        void display() const;

        std::string getAuthor() const;
        std::string getTitle() const;
        int getYear() const;
        bool getAvailability() const;

        void setAvailability(bool dispo);

    private:
        std::string title;
        std::string author;
        int year;
        bool available;
};

/******************************************************************************************
 * Overloading of the operators
 ******************************************************************************************/

std::ostream& operator<<(std::ostream& os, const Book& livre);

#endif  // INCLUDE_LIVRE_HPP_
