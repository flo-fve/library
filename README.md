# Library manager

## About

The aim of this training project is to develop a library of books allowing users to:
- view the books available
- search for a book by title or author
- borrow or return a book

A book is defined by its title, author, publication date, and availability for borrowing.

## Build the project

The whole project is written in C++20. It is compiled and built with CMake version 3.20 minimum.
The Graphical User Interface (GUI) is made with Qt5 and Qt Designer.

At the root of the project, launch the following commands:
```bash
mkdir build
cmake -B build
cmake --build build
```

## Code quality

`pre-commit` hooks are used in order to ensure code quality:
- `clang-format`
- `clang-tidy`
- `cppcheck`

These executables should be installed to make the hooks work.

A Python virtual environment is recommended to install `pre-commit`.
