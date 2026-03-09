// Copyright 2026 Florian Favre

#include <QApplication>
#include <string>

#include "MainWindow.hpp"

using namespace std;

/******************************************************************************************
 * Main
 ******************************************************************************************/

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

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
