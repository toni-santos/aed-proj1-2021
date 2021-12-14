#ifndef AED_PROJ_2021_USER_INTERFACE_H
#define AED_PROJ_2021_USER_INTERFACE_H

#include "Company.h"

enum Menu {
    EXIT,
    MAIN,

    CLIENT,
    CLIENT_OPTIONS,
    CHECK_FLIGHTS,
    BUY_TICKETS,

    EMPLOYEE,
    EMPLOYEE_OPTIONS,
    PLANES,
    FLIGHTS,
    SERVICES,
    CLIENTS,
};

class UserInterface {
    /**
     * @brief Specifies which menu to show.
     */
    Menu _currentMenu = MAIN;
    /**
     * @brief The error message to show.
     */
    std::string _errorMessage{};

    /**
     * @brief Helper method to show a menu with options.
     *
     * @details Each option string will be shown along with its index on the
     *          list. When the user inputs one of the indices of the list
     *          _currentMenu will be set to that option's Menu.
     *
     * @note The first option on the list will be shown last and is
     *       intended to be a way to go back in the navigation tree.
     *
     * @note This can show an arbitrary amount of options, but only navigate to
     *       the first 10 options.
     *
     * @param text Text to show before the options
     * @param options The list of options to show
     */
    void optionsMenu(const std::string &text,
                     const std::vector<std::pair<std::string, Menu>> &options);

    /**
     * @brief Shows the main menu.
     */
    void mainMenu();
    /**
     * @brief Shows the employee menu.
     */
    void employeeMenu();
    /**
     * @brief Shows the employee options menu.
     */
    void employeeOptionsMenu();
    /**
     * @brief Shows the client menu.
     */
    void clientMenu();
    /**
     * @brief Shows the client options menu.
     */
    void clientOptionsMenu();

public:
    /**
     * @brief Shows the current menu.
     *
     * @param comp
     */
    void show(Company comp);
    /**
     * @brief Shows a message before the program exits.
     */
    void exit();
};

#endif // AED_PROJ_2021_MENU_H
