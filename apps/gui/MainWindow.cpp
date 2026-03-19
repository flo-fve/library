// Copyright 2026 Florian Favre

#include "MainWindow.hpp"

#include <QMessageBox>

#include "AddBookDialog.hpp"
#include "Book.hpp"
#include "Library.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

MainWindow::MainWindow(Library& library)
    : QMainWindow(nullptr), ui(new Ui::MainWindow), library(library) {
    ui->setupUi(this);

    // Set table columns behavior
    ui->table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // Connect buttons to slots
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addBook);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeSelectedBook);

    populateTable();
}

MainWindow::~MainWindow() {
    delete ui;
}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

void MainWindow::populateTable() {
    const auto& books = library.getBooks();

    ui->table->setRowCount(books.size());

    for (size_t i = 0; i < books.size(); ++i) {
        ui->table->setItem(i, 0,
                           new QTableWidgetItem(QString::fromStdString(books[i].getAuthor())));
        ui->table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(books[i].getTitle())));
        ui->table->setItem(i, 2, new QTableWidgetItem(QString::number(books[i].getYear())));
        ui->table->setItem(i, 3, new QTableWidgetItem(QString::number(books[i].getAvailability())));
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
    int selectedRow = ui->table->currentRow();

    if (selectedRow == -1) {
        QMessageBox::warning(this, "No selection", "Please select a book to remove.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm", "Remove the selected book?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QString author = ui->table->item(selectedRow, 0)->text();
        QString title = ui->table->item(selectedRow, 1)->text();
        library.removeBook(author.toStdString(), title.toStdString());
        ui->table->removeRow(selectedRow);
    }
}
