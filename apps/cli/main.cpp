// Copyright 2026 Florian Favre

#include <iostream>
#include <vector>

#include "CliApp.hpp"
#include "Library.hpp"

using namespace std;

/******************************************************************************************
 * Main
 ******************************************************************************************/

int main(int argc, const char* argv[]) {
    string data;

    if (argc == 2) {
        data = argv[1];
    } else {
        data = "";
    }

    Library library(data);

    CliApp app(library);

    app.execute();

    return 0;
}
