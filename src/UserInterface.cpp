#include "../includes/UserInterface.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>

void UserInterface::optionsMenu(
    const std::string &text,
    const std::vector<std::pair<std::string, Menu>> &options) {
    std::cout << CLEAR_SCREEN << text << "\n\n";

    for (int i{1}; i < options.size(); ++i) {
        std::cout << "(" << i << ") " << options.at(i).first << std::endl;
    }

    std::cout << "(0) " << options.front().first << "\n\n";
    std::cout << ERROR_MESSAGE << _errorMessage << RESET_FORMATTING;
    _errorMessage = "";
    std::cout << "Please insert option: " << std::flush;

    std::string input;
    getInput(input);

    if (input.size() != 1 || !isdigit(input.at(0))) {
        _errorMessage = "Invalid input!\n";
        return;
    }

    unsigned option = input.at(0) - '0';

    if (option < options.size())
        _currentMenu = options.at(option).second;
    else
        _errorMessage = "Invalid option!\n";
}

bool validCredentials(std::string &username, std::string &password) {
    return username == "admin" && password == "admin";
}

void UserInterface::clientMenu() {
    std::cout << CLEAR_SCREEN << "Welcome to " << STRIKE_THROUGH << "[REDACTED]"
              << RESET_FORMATTING
              << " Airlines!\n"
                 "We are connecting you to our services..."
              << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    _currentMenu = CLIENT_OPTIONS;
    throw Exit();
}

void UserInterface::employeeMenu() {
    std::string username, password;

    std::cout << CLEAR_SCREEN
              << "Please enter your credentials\n"
                 "Username: "
              << std::flush;

    getInput(username);

    std::cout << "Password: " << CONCEAL_TEXT << DISABLE_CURSOR;

    getInput(password);

    std::cout << ENABLE_CURSOR << RESET_FORMATTING;

    if (validCredentials(username, password)) {
        _currentMenu = EMPLOYEE_OPTIONS;
    } else {
        _currentMenu = MAIN;
    }
}

void UserInterface::mainMenu() {
    optionsMenu("COMPANY NAME",
                {{"Exit", EXIT}, {"Client", CLIENT}, {"Employee", EMPLOYEE}});
}

void UserInterface::employeeOptionsMenu() {
    optionsMenu("[REDACTED] AIRLINES - ADMIN", {{"Log Off", MAIN},
                                                {"Planes", PLANES},
                                                {"Flights", FLIGHTS},
                                                {"Services", SERVICES},
                                                {"Clients", CLIENTS}});
}

void UserInterface::clientOptionsMenu() {
    optionsMenu("[REDACTED] AIRLINES", {{"Go back", MAIN},
                                        {"Check Flights", CHECK_FLIGHTS},
                                        {"Buy Tickets", BUY_TICKETS}});
}

void UserInterface::show(Company comp) {
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

void UserInterface::exit() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::cout << "Shutting down ✈" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "\e[2D. ✈" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "\e[2D. ✈" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::cout << "\e[2D. ✈" << std::endl;
}
