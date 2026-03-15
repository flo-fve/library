// Copyright 2026 Florian Favre

#include <QApplication>
#include <QFile>
#include <string>

#include "MainWindow.hpp"

using namespace std;

/******************************************************************************************
 * Main
 ******************************************************************************************/

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Load the syle file
    QFile styleFile(":/resources/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        app.setStyleSheet(styleFile.readAll());
        styleFile.close();
    }

    // Instanciate the library
    string data;

    if (argc == 2) {
        data = argv[1];
    } else {
        data = "";
    }

    Library library(data);

    MainWindow window(library);
    window.show();

    return app.exec();
}
