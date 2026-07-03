#include <gtest/gtest.h>

#include <format>

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

TEST(LibraryTest, SearchByAuthorTest) {
    Library library;

    // Add books to the library
    Book book1("Title 1", "Author 1", 2026, true);
    Book book2("Title 1", "Author 2", 2022, true);
    Book book3("Title 2", "Author 2", 2023, true);
    Book book4("Title 3", "Author 2", 2024, true);
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    library.addBook(book4);

    // Search books from Author 1
    std::vector<Book> results_1 = library.searchByAuthor("Author 1");

    ASSERT_EQ(results_1.size(), 1) << "Author 1 should have 1 book";

    EXPECT_EQ(results_1[0].getAuthor(), "Author 1") << "The author should be `Author 1`";
    EXPECT_EQ(results_1[0].getTitle(), "Title 1") << "The title should be `Title 1`";
    EXPECT_EQ(results_1[0].getYear(), 2026) << "The year should be `2026`";

    // Search books from Author 2
    std::vector<Book> results_2 = library.searchByAuthor("Author 2");

    ASSERT_EQ(results_2.size(), 3) << "Author 2 should have 3 books";

    EXPECT_EQ(results_2[0].getAuthor(), "Author 2") << "The author should be `Author 2`";
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(results_2[i].getTitle(), std::format("Title {}", i + 1))
            << std::format("The title should be `Title {}`", i + 1);
        EXPECT_EQ(results_2[i].getYear(), 2022 + i)
            << std::format("The year should be `{}`", 2022 + i);
    }

    // Search books from Author 3
    std::vector<Book> results_3 = library.searchByAuthor("Author 3");

    ASSERT_EQ(results_3.size(), 0) << "Author 3 should have 0 book";
}

TEST(LibraryTest, SearchByTitleTest) {
    Library library;

    // Add books to the library
    Book book1("Title 1", "Author 1", 2026, true);
    Book book2("Title 1", "Author 2", 2022, true);
    Book book3("Title 2", "Author 2", 2023, true);
    Book book4("Title 3", "Author 2", 2024, true);
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    library.addBook(book4);

    // Search books named Title 1
    std::vector<Book> results_1 = library.searchByTitle("Title 1");

    ASSERT_EQ(results_1.size(), 2) << "There should be 2 books named `Title 1`";

    EXPECT_EQ(results_1[0].getTitle(), "Title 1") << "The title should be `Title 1`";
    EXPECT_EQ(results_1[1].getTitle(), "Title 1") << "The title should be `Title 1`";

    EXPECT_EQ(results_1[0].getAuthor(), "Author 1") << "The author should be `Author 1`";
    EXPECT_EQ(results_1[1].getAuthor(), "Author 2") << "The author should be `Author 2`";

    EXPECT_EQ(results_1[0].getYear(), 2026) << "The year should be `2026`";
    EXPECT_EQ(results_1[1].getYear(), 2022) << "The year should be `2022`";

    // Search books named Title 2
    std::vector<Book> results_2 = library.searchByTitle("Title 2");

    ASSERT_EQ(results_2.size(), 1) << "There should be 1 book named `Title 2`";

    EXPECT_EQ(results_2[0].getTitle(), "Title 2") << "The title should be `Title 2`";

    EXPECT_EQ(results_2[0].getAuthor(), "Author 2") << "The author should be `Author 2`";

    EXPECT_EQ(results_2[0].getYear(), 2023) << "The year should be `2023`";

    // Search books named Title X
    std::vector<Book> results_3 = library.searchByTitle("Title X");

    ASSERT_EQ(results_3.size(), 0) << "There should be no book named `Title X`";
}
