#include <gtest/gtest.h>

#include "Book.hpp"
#include "Library.hpp"

TEST(LibraryTest, AddBookTest) {
    Library library;

    EXPECT_EQ(library.numberAuthors(), 0);
    EXPECT_EQ(library.numberBooks(), 0);

    // Add a new book and a new author entry
    Book book("Title", "Author", 2026);
    library.addBook(book);

    EXPECT_EQ(library.numberAuthors(), 1);
    EXPECT_EQ(library.numberBooks(), 1);

    // Add a new book with the same author
    Book bookBis("Another title", "Author", 2023);
    library.addBook(bookBis);

    EXPECT_EQ(library.numberAuthors(), 1);
    EXPECT_EQ(library.numberBooks(), 2);
}

TEST(LibraryTest, RemoveBookTest) {
    Library library;

    // Add a new book and a new author entry
    Book book("Title", "Author", 2026);
    library.addBook(book);

    EXPECT_EQ(library.numberAuthors(), 1);
    EXPECT_EQ(library.numberBooks(), 1);

    // Remove this book
    library.removeBook("Author", "Title");

    EXPECT_EQ(library.numberAuthors(), 0);
    EXPECT_EQ(library.numberBooks(), 0);
}

TEST(LibraryTest, BorrowBookTest) {
    Library library;

    // Add books to the library
    Book book1("Title 1", "Author 1", 2026, true);
    Book book2("Title 2", "Author 2", 2024, true);
    Book book3("Another Title 2", "Author 2", 2018, false);
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    // Borrow available books
    EXPECT_TRUE(library.borrowBook("Author 1", "Title 1"));
    EXPECT_TRUE(library.borrowBook("Author 2", "Title 2"));

    // Try to borrow already borrowed book
    EXPECT_FALSE(library.borrowBook("Author 1", "Title 1"));

    // Borrow unvailable book
    EXPECT_FALSE(library.borrowBook("Author 2", "Another Title 2"));
}

TEST(LibraryTest, ReturnBookTest) {
    Library library;

    // Add books to the library
    Book book1("Title 1", "Author 1", 2026, false);
    Book book2("Title 2", "Author 2", 2024, false);
    Book book3("Another Title 2", "Author 2", 2018, true);
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    // Return books
    EXPECT_TRUE(library.returnBook("Author 1", "Title 1"));
    EXPECT_TRUE(library.returnBook("Author 2", "Title 2"));

    // Try to return already returned book
    EXPECT_FALSE(library.returnBook("Author 1", "Title 1"));

    // Return available book
    EXPECT_FALSE(library.returnBook("Author 2", "Another Title 2"));
}
