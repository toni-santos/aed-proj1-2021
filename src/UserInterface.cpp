#include "../includes/UserInterface.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
#include <chrono>
#include <iostream>
#include <sstream>
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
    std::string userNIF;

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
    std::string curr;
    std::cout << CLEAR_SCREEN << "Welcome to " << STRIKE_THROUGH << "[REDACTED]"
              << RESET_FORMATTING << " Airlines!" << std::endl;
    std::cout << "Please enter your NIF:" << std::flush;
    getInput(curr);
    userNIF = stoul(curr);
    loadString("Connecting you to our services...", 3000);
    _currentMenu = CLIENT_OPTIONS;
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
    optionsMenu("[REDACTED] AIRLINES - ADMIN", {{"Log off", MAIN},
                                                {"Planes", PLANES},
                                                {"Flights", FLIGHTS},
                                                {"Services", SERVICES},
                                                {"Clients", CLIENTS}});
}

void UserInterface::clientOptionsMenu() {
    optionsMenu("[REDACTED] AIRLINES - Welcome " + std::to_string(userNIF) +
                    " !",
                {{"Go back", MAIN},
                 {"Check my flights", CHECK_FLIGHTS},
                 {"Buy tickets", BUY_TICKETS}});
}

void UserInterface::clientsMenu(Company &comp) {
    std::stringstream text;
    text << "These are all the clients:\n\n";

    for (const Client &client : comp.getClients()) {
        text << client.getNIF() << '\t' << client.getName() << '\n';
    }

    text << "\nWhat do you want to do?";

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New client", CREATE_CLIENT},
                             {"Client info", READ_CLIENT},
                             {"Update client", UPDATE_CLIENT},
                             {"Delete client", DELETE_CLIENT}});
}

void UserInterface::clientsFlightsMenu(Company &comp) {
    for (const Client &client : comp.getClients()) {
        if (client.getNIF() == userNIF) {
            for (auto ticket : client.getTickets()) {
                std::cout << ticket.getID() << '\t' << ticket.getFlightID()
                          << std::endl;
            }
        }
    }
    std::cout << "Press Enter to go back!" << std::endl;
    _currentMenu = MAIN;
}

void UserInterface::show(Company &comp) {
    switch (_currentMenu) {
    case CLIENT:
        clientMenu();
        break;
    case CLIENT_OPTIONS:
        clientOptionsMenu();
        break;

    case EMPLOYEE:
        employeeMenu();
        break;
    case EMPLOYEE_OPTIONS:
        employeeOptionsMenu();
        break;
    case CLIENTS:
        clientsMenu(comp);
        break;

    case MAIN:
        mainMenu();
        break;
    case CHECK_FLIGHTS:
        clientsFlightsMenu(comp);
        break;
    default:
        throw Exit();
        break;
    }
}

void UserInterface::loadString(const std::string &text, unsigned time) const {
    unsigned inc = time / text.size();

    std::cout << " ✈" << std::flush;
    for (char c : text) {
        std::cout << "\e[2D" << c << " ✈" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(inc));
    }
    std::cout << std::endl;
}

void UserInterface::exit() {
    std::cout << CLEAR_SCREEN << std::flush;
    // std::cout << "Shutting down ✈" << std::flush;
    // std::this_thread::sleep_for(std::chrono::milliseconds(250));
    // std::cout << "\e[2D. ✈" << std::flush;
    // std::this_thread::sleep_for(std::chrono::milliseconds(250));
    // std::cout << "\e[2D. ✈" << std::flush;
    // std::this_thread::sleep_for(std::chrono::milliseconds(250));
    // std::cout << "\e[2D. ✈" << std::endl;
    loadString("Shutting down...", 1000);
}
