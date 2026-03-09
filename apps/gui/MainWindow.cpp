// Copyright 2026 Florian Favre

#include "MainWindow.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

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
    table = new QTableWidget(0, 2);
    table->setHorizontalHeaderLabels({"Author", "Title"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Buttons
    addButton = new QPushButton("Add");
    removeButton = new QPushButton("Remove");

    auto* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);

    // Layout assembly
    mainLayout->addWidget(searchBar);
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);

    central->setLayout(mainLayout);
    setCentralWidget(central);

    resize(600, 400);
    setWindowTitle("Library");

    populateTable();
}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void MainWindow::populateTable() {
    const auto& books = library.getBooks();

    table->setRowCount(books.size());

    for (size_t i = 0; i < books.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(books[i].getAuthor())));

        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(books[i].getTitle())));
    }
}
