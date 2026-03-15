// Copyright 2026 Florian Favre

#include "AddBookDialog.hpp"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

AddBookDialog::AddBookDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Add Book");

    titleEdit = new QLineEdit;
    authorEdit = new QLineEdit;
    yearEdit = new QLineEdit;

    auto* formLayout = new QFormLayout;
    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Author:", authorEdit);
    formLayout->addRow("Year:", yearEdit);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);

    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto* layout = new QVBoxLayout;
    layout->addLayout(formLayout);
    layout->addWidget(buttons);

    setLayout(layout);
}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

std::string AddBookDialog::getTitle() const {
    return titleEdit->text().toStdString();
}

std::string AddBookDialog::getAuthor() const {
    return authorEdit->text().toStdString();
}

int AddBookDialog::getYear() const {
    return yearEdit->text().toInt();
}
