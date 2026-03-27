// Copyright 2026 Florian Favre

#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>

#include "Library.hpp"
#include "ui_MainWindow.h"

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
        Ui::MainWindow* ui;
        Library& library;

        void populateTable();

        void addBook();
        void removeSelectedBook();
        void borrowBook();
        void returnBook();
};

#endif  // MAINWINDOW_HPP_
