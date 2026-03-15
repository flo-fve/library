// Copyright 2026 Florian Favre

#include "MainWindow.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "AddBookDialog.hpp"
#include "Book.hpp"
#include "Library.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

MainWindow::MainWindow(Library& library) : library(library) {
    auto* central = new QWidget;
    auto* mainLayout = new QVBoxLayout;

    // Search bar
    searchBar = new QLineEdit;
    searchBar->setPlaceholderText("Search...");

    // Table
    table = new QTableWidget(0, 4);
    table->setHorizontalHeaderLabels({"Author", "Title", "Year", "Available"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Buttons layout
    auto* buttonsLayout = new QHBoxLayout;
    auto* buttonWidget = new QWidget;

    buttonWidget->setLayout(buttonsLayout);
    buttonWidget->setStyleSheet("QWidget { border: 1px solid gray; padding: 4px; }");

    // Add book dialog
    addButton = new QPushButton("Add", this);
    buttonsLayout->addWidget(addButton);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addBook);

    // Remove button
    removeButton = new QPushButton("Remove selected", this);
    removeButton->setObjectName("removeButton");
    buttonsLayout->addWidget(removeButton);

    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeSelectedBook);

    // Layout assembly
    mainLayout->addWidget(searchBar);
    mainLayout->addWidget(table);
    mainLayout->addWidget(buttonWidget);

    central->setLayout(mainLayout);
    setCentralWidget(central);

    resize(600, 400);
    setWindowTitle("Library");

    populateTable();
}

MainWindow::~MainWindow() {}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void MainWindow::populateTable() {
    const auto& books = library.getBooks();

    table->setRowCount(books.size());

    for (size_t i = 0; i < books.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(books[i].getAuthor())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(books[i].getTitle())));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(books[i].getYear())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(books[i].getAvailability())));
    }
}

void MainWindow::addBook() {
    AddBookDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        std::string title = dialog.getTitle();
        std::string author = dialog.getAuthor();
        int year = dialog.getYear();

        if (!title.empty() && !author.empty()) {
            Book book(title, author, year);
            library.addBook(author, book);

            populateTable();
        }
    }
}

void MainWindow::removeSelectedBook() {
    int selectedRow = table->currentRow();

    if (selectedRow == -1) {
        QMessageBox::warning(this, "No selection", "Please select a book to remove.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm", "Remove the selected book?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QString author = table->item(selectedRow, 0)->text();
        QString title = table->item(selectedRow, 1)->text();
        library.removeBook(author.toStdString(), title.toStdString());
        table->removeRow(selectedRow);
    }
}
