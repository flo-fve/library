#include <gtest/gtest.h>

#include "Book.hpp"
#include "Library.hpp"

TEST(LibraryTest, AddBookTest) {
    Library library;

    EXPECT_EQ(library.numberAuthors(), 0);
    EXPECT_EQ(library.numberBooks(), 0);

    // Add a new book and a new author entry
    Book book("Title", "Author", 2026);
    library.addBook("Author", book);

    EXPECT_EQ(library.numberAuthors(), 1);
    EXPECT_EQ(library.numberBooks(), 1);

    // Add a new book with the same author
    Book bookBis("Another title", "Author", 2023);
    library.addBook("Author", bookBis);

    EXPECT_EQ(library.numberAuthors(), 1);
    EXPECT_EQ(library.numberBooks(), 2);
}

TEST(LibraryTest, RemoveBookTest) {
    Library library;

    // Add a new book and a new author entry
    Book book("Title", "Author", 2026);
    library.addBook("Author", book);

    EXPECT_EQ(library.numberAuthors(), 1);
    EXPECT_EQ(library.numberBooks(), 1);

    // Remove this book
    library.removeBook("Author", "Title");

    EXPECT_EQ(library.numberAuthors(), 0);
    EXPECT_EQ(library.numberBooks(), 0);
}
