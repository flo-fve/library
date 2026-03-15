// Copyright 2026 Florian Favre

#ifndef ADDBOOKDIALOG_HPP_
#define ADDBOOKDIALOG_HPP

#include <QDialog>

/******************************************************************************************
 * Definition of the classes
 ******************************************************************************************/

class QLineEdit;

class AddBookDialog : public QDialog {
        Q_OBJECT

    public:
        explicit AddBookDialog(QWidget* parent = nullptr);

        std::string getTitle() const;
        std::string getAuthor() const;
        int getYear() const;

    private:
        QLineEdit* titleEdit;
        QLineEdit* authorEdit;
        QLineEdit* yearEdit;
};

#endif  // ADDBOOKDIALOG_HPP_
