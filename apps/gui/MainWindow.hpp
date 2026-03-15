// Copyright 2026 Florian Favre

#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>

#include "Library.hpp"

/******************************************************************************************
 * Definition of the classes
 ******************************************************************************************/

class QLineEdit;
class QTableWidget;
class QPushButton;

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(Library& library);
        ~MainWindow();

    private:
        Library& library;

        QLineEdit* searchBar;
        QTableWidget* table;
        QPushButton* addButton;
        QPushButton* removeButton;

        void populateTable();

        void addBook();
        void removeSelectedBook();
};

#endif  // MAINWINDOW_HPP_
