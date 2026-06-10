#ifndef CLI_APP_HPP
#define CLI_APP_HPP

#include "../../include/Library.hpp"
#include "MenuStates.hpp"

/******************************************************************************************
 * Definition of the class
 ******************************************************************************************/

class CliApp {
    public:
        explicit CliApp(Library& library);
        ~CliApp();

        void execute();

    private:
        Library& library;
        MenuState currentState;

        int displayMenuMain();
        int displaySubMenuBooks();
        int displaySubSubMenuSearch();
};

#endif  // CLI_APP_HPP
