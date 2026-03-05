#include <gtest/gtest.h>

#include "Book.hpp"

TEST(BookTest, GetAuthorTest) {
    Book book("My Book", "The author", 2026);

    ASSERT_EQ(book.getAuthor(), "The author");
}

TEST(BookTest, GetTitleTest) {
    Book book("My Book", "The author", 2026);

    ASSERT_EQ(book.getTitle(), "My Book");
}

TEST(BookTest, GetYearTest) {
    Book book("My Book", "The author", 2026);

    ASSERT_EQ(book.getYear(), 2026);
}

TEST(BookTest, GetAvailability) {
    Book book("My Book", "The author", 2026, true);

    ASSERT_TRUE(book.getAvailability());
}

TEST(BookTest, SetAvailability) {
    Book book("My Book", "The author", 2026, true);

    ASSERT_TRUE(book.getAvailability());

    book.setAvailability(false);

    ASSERT_FALSE(book.getAvailability());
}
