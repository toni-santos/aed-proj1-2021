#include "../includes/Menu.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>

void Menu::optionsMenu(
    const std::string &menu,
    const std::vector<std::pair<std::string, MenuType>> &options) {
    std::cout << clearScreen << menu << "\n\n";

    for (int i{0}; i < options.size() - 1; ++i) {
        std::cout << "(" << i + 1 << ") " << options.at(i).first << std::endl;
    }

    std::cout << "(0) " << options.at(options.size() - 1).first << "\n\n";
    std::cout << errorMessage << _errorMessage << reset;
    _errorMessage = "";
    std::cout << "Please insert option: " << std::flush;

    std::string input;
    getInput(input);

    if (input.size() != 1 || !isdigit(input.at(0))) {
        _errorMessage = "Invalid input!\n";
        return;
    }

    int option = input.at(0) - '0';

    if (option == 0)
        _currentMenu = options.back().second;
    else if (option < options.size())
        _currentMenu = options.at(option - 1).second;
    else
        _errorMessage = "Invalid option!\n";
}

bool validCredentials(std::string &username, std::string &password) {
    return username == "admin" && password == "admin";
}

void Menu::clientMenu() {
    std::cout << clearScreen
              << "Welcome to \e[9m[REDACTED]\e[0m Airlines!\n"
                 "We are connecting you to our services..."
              << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    _currentMenu = CLIENT_OPTIONS;
    throw Exit();
}

void Menu::employeeMenu() {
    std::string username, password;

    std::cout << clearScreen
              << "Please enter your credentials\n"
                 "Username: "
              << std::flush;

    getInput(username);

    std::cout << "Password: \e[8m\e[?25l";

    getInput(password);

    std::cout << "\e[?25h\e[0m";

    if (validCredentials(username, password)) {
        _currentMenu = EMPLOYEE_OPTIONS;
    } else {
        _currentMenu = MAIN;
    }
}

void Menu::mainMenu() {
    optionsMenu("COMPANY NAME",
                {{"Client", CLIENT}, {"Employee", EMPLOYEE}, {"Exit", EXIT}});
}

void Menu::employeeOptionsMenu() {
    optionsMenu("[REDACTED] AIRLINES - ADMIN", {{"Planes", PLANES},
                                                {"Flights", FLIGHTS},
                                                {"Services", SERVICES},
                                                {"Clients", CLIENTS},
                                                {"Log Off", MAIN}});
}

void Menu::clientOptionsMenu() {
    optionsMenu("[REDACTED] AIRLINES", {{"Check Flights", CHECK_FLIGHTS},
                                        {"Buy Tickets", BUY_TICKETS},
                                        {"Go back", MAIN}});
}

void Menu::menu(Company comp) {
    switch (_currentMenu) {
    case MAIN:
        mainMenu();
        break;
    case EMPLOYEE:
        employeeMenu();
        break;
    case CLIENT:
        clientMenu();
        break;
    case EMPLOYEE_OPTIONS:
        employeeOptionsMenu();
        break;
    case CLIENT_OPTIONS:
        clientOptionsMenu();
        break;
    default:
        throw Exit();
        break;
    }
}

void Menu::exit() {
    std::cout << clearScreen << std::flush;
    std::cout << "Shutting down ✈" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "\e[2D. ✈" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "\e[2D. ✈" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "\e[2D. ✈" << std::endl;
}
