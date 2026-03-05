#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "utils.hpp"

TEST(SplitStringTest, SimpleTest) {
    std::string s = "foo,bar,boo,loo";
    std::string delimiter = ",";
    std::vector<std::string> res = {"foo", "bar", "boo", "loo"};
    EXPECT_EQ(splitString(s, delimiter), res);
}

TEST(SlugifyTest, BasicSentence) {
    EXPECT_EQ(slugify("Hello World"), "hello-world");
}

TEST(SlugifyTest, MultipleAccents) {
    EXPECT_EQ(slugify("ééé"), "eee");
}

TEST(SlugifyTest, RemoveCapitalAccents) {
    EXPECT_EQ(slugify("Éléphant à l'École"), "elephant-a-lecole");
}

TEST(SlugifyTest, MultipleSpaces) {
    EXPECT_EQ(slugify("  hello   world  "), "hello-world");
}

TEST(SlugifyTest, SpecialCharacters) {
    EXPECT_EQ(slugify("C++ Programming!!!"), "c-programming");
}

TEST(SlugifyTest, EmptyString) {
    EXPECT_EQ(slugify(""), "");
}
