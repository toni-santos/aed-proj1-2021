#ifndef AED_PROJ_2021_MENU_H
#define AED_PROJ_2021_MENU_H

#include "Company.h"

enum MenuType {
    MAIN,
    EMPLOYEE,
    CLIENT,
    EMPLOYEE_OPTIONS,
    CLIENT_OPTIONS,
    CHECK_FLIGHTS,
    BUY_TICKETS,
    PLANES,
    FLIGHTS,
    SERVICES,
    CLIENTS,
    EXIT
};

class Menu {
    MenuType _currentMenu = MAIN;
    std::string _errorMessage{};

    void
    optionsMenu(const std::string &menu,
                const std::vector<std::pair<std::string, MenuType>> &options);

    void mainMenu();
    void employeeMenu();
    void employeeOptionsMenu();
    void clientMenu();
    void clientOptionsMenu();

public:
    void menu(Company comp);
    void exit();
};

#endif // AED_PROJ_2021_MENU_H
