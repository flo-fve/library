# Library manager

## About

The aim of this training project is to develop a library of books allowing users to:
- view the books available
- search for a book by title or author
- borrow or return a book

A book is defined by its title, author, publication date, and availability for borrowing.

## Code quality

`pre-commit` hooks are used in order to ensure code quality:
- `clang-format`
- `clang-tidy`
- `cppcheck`

These executables should be installed to make the hooks work.

A Python virtual environment is recommended to install `pre-commit`.
