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
    public:
        explicit MainWindow(Library& library);

    private:
        Library& library;

        QLineEdit* searchBar;
        QTableWidget* table;
        QPushButton* addButton;
        QPushButton* removeButton;

        void populateTable();
};

#endif  // MAINWINDOW_HPP_
