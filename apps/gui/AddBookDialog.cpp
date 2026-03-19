// Copyright 2026 Florian Favre

#include "AddBookDialog.hpp"

/******************************************************************************************
 * Constructor and destructor
 ******************************************************************************************/

AddBookDialog::AddBookDialog(QWidget* parent) : QDialog(parent), ui(new Ui::AddBookDialog) {
    ui->setupUi(this);
}

AddBookDialog::~AddBookDialog() {
    delete ui;
}

/******************************************************************************************
 * Methods
 ******************************************************************************************/

std::string AddBookDialog::getTitle() const {
    return ui->titleEdit->text().toStdString();
}

std::string AddBookDialog::getAuthor() const {
    return ui->authorEdit->text().toStdString();
}

int AddBookDialog::getYear() const {
    return ui->yearEdit->text().toInt();
}
