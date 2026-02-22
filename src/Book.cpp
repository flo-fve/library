// Copyright 2026 Florian Favre

#include "Book.hpp"

#include <iostream>

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

Book::Book() : title("Title"), author("Author"), year(2026), available(1) {}

Book::Book(std::string const& title, std::string const& author, int year)
    : title(title), author(author), year(year), available(1) {}

Book::Book(std::string const& title, std::string const& author, int year, bool available)
    : title(title), author(author), year(year), available(available) {}

Book::~Book() {}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void Book::display() const {
    std::string disp = available ? "available" : "not available";
    std::cout << title << ", " << author << " (" << year << "), " << disp << "\n";
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getTitle() const {
    return title;
}

int Book::getYear() const {
    return year;
}

bool Book::getAvailability() const {
    return available;
}

void Book::setAvailability(bool dispo) {
    available = dispo;
}

/******************************************************************************************
 * Overloading of the operators
 ******************************************************************************************/

std::ostream& operator<<(std::ostream& os, const Book& livre) {
    livre.display();
    return os;
}
