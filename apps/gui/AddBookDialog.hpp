// Copyright 2026 Florian Favre

#ifndef ADDBOOKDIALOG_HPP_
#define ADDBOOKDIALOG_HPP

#include <QDialog>

#include "ui_AddBookDialog.h"

/******************************************************************************************
 * Definition of the classes
 ******************************************************************************************/

class QLineEdit;

class AddBookDialog : public QDialog {
        Q_OBJECT

    public:
        explicit AddBookDialog(QWidget* parent = nullptr);
        ~AddBookDialog();

        std::string getTitle() const;
        std::string getAuthor() const;
        int getYear() const;

    private:
        Ui::AddBookDialog* ui;
};

#endif  // ADDBOOKDIALOG_HPP_
