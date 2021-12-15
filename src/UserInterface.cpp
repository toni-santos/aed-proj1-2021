#include "../includes/UserInterface.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
#include <algorithm>
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

bool isDigitOnly(std::string strNIF) {
    return std::all_of(strNIF.begin(), strNIF.end(),
                       [](char c) { return std::isdigit(c); });
}

void UserInterface::clientMenu(Company &comp) {
    std::string userNIF, name;
    std::cout << CLEAR_SCREEN << "Welcome to " << STRIKE_THROUGH << "[REDACTED]"
              << RESET_FORMATTING << " Airlines!" << std::endl;
    std::cout << "Please enter your NIF:" << std::flush;
    getInput(userNIF);
    for (Client c : comp.getClients()) {
        if (c.getNIF() == stoul(userNIF)) {
            currClient = &c;
            loadString("Connecting you to our services...", 3000);
            _currentMenu = CLIENT_OPTIONS;
        }
    }

    std::cout << "It seems you have never travelled with us... :(\n"
              << "To finish your registration insert your name: " << std::flush;

    getInput(name);

    if (isDigitOnly(userNIF)) {
        Client client = Client(name, stoul(userNIF));
        comp.addClient(client);
        std::cout << "Thanks for choosing " << STRIKE_THROUGH << "[REDACTED]"
                  << RESET_FORMATTING << " Airlines!" << std::endl;
        _currentMenu = CLIENT_OPTIONS;
        currClient = &comp.getClients().back();
    }
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
    optionsMenu("[REDACTED] AIRLINES - Welcome " +
                    std::to_string(currClient->getNIF()) + " !",
                {{"Go back", MAIN},
                 {"Check my flights", CHECK_FLIGHTS},
                 {"Buy tickets", BUY_TICKETS}});
}

void UserInterface::servicesMenu(Company &comp) {
    std::stringstream text;
    std::string p;
    text << "These are all the planes:\n\n";
    text << "ID\n\n";
    for (const Plane &plane : comp.getPlanes()) {
        std::string fls;
        for (unsigned i : plane.getFlights()) {
            fls += " " + i;
        }
        text << plane.getID() << '\n';
    }

    text << "\nChoose a plane...";
    getInput(p);

    for (const Plane &plane : comp.getPlanes()) {
        if (p = plane.getID()) {
            optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                                     {"New service", CREATE_SERVICE},
                                     {"Check services", READ_SERVICE},
                                     {"Complete service", DELETE_SERVICE}});
        }
    }
}

void UserInterface::planesMenu(Company &comp) {
    std::stringstream text;
    text << "These are all the planes:\n\n";
    text << "ID - Type - Plate - Capacity - Duration - Flights\n\n";
    for (const Plane &plane : comp.getPlanes()) {
        std::string fls;
        for (unsigned i : plane.getFlights()) {
            fls += " " + i;
        }
        text << plane.getID() << " - " << plane.getPlate() << " - "
             << plane.getPlate() << " - " << plane.getCapacity() << " -" << fls
             << '\n';
    }

    text << "\nChoose an operation...";

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New plane", CREATE_PLANE},
                             {"Plane info", READ_PLANE},
                             {"Update plane", UPDATE_PLANE},
                             {"Delete plane", DELETE_PLANE}});
}

void UserInterface::createPlane(Company &comp) {
    std::string plate, type, strCapacity, strId;
    unsigned capacity, id;

    std::cout << "Insert the plane's plate: " << std::flush;
    getInput(plate);

    std::cout << "Insert the plane's type: " << std::flush;
    getInput(type);

    std::cout << "Insert the plane's capacity: " << std::flush;
    getInput(strCapacity);

    std::cout << "Insert the plane's capacity: " << std::flush;
    getInput(strId);

    // TODO: check if id doesnt exist I WONDER IF THAT WOULD BE EASIER WITH
    // ANOTHER TOOL HAHA MAYBE SQL OR SOME SORT OF DB LANGUAGE HAHA OH WELL
    // THATS JUST ME IM QUIRKY LIKE THAT XD

    if (isDigitOnly(strCapacity) && isDigitOnly(strId)) {
        std::cout << "\nCreating the plane..." << std::flush;
        Plane plane = Plane(plate, type, stoul(capacity), stoul(id));
        comp.addPlane(plane);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Returning to the previous menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _currentMenu = PLANES;
    }
}

void UserInterface::checkPlane(Company &comp) {}

void UserInterface::updatePlane(Company &comp) {}

void UserInterface::deletePlane(Company &comp) {}

void UserInterface::flightsMenu(Company &comp) {
    std::stringstream text;
    text << "These are all the flights:\n\n";
    text << "Number - Departure Date - Origin->Destination - Duration\n\n";
    for (const Flight &flight : comp.getFlights()) {
        text << flight.getNumber() << " - " << flight.getDepartureDate()
             << " - " << flight.getOrigin() << "->" << flight.getDestination()
             << " - " << flight.getDuration() << '\n';
    }

    text << "\nChoose an operation...";

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New flight", CREATE_FLIGHT},
                             {"Check flight", READ_FLIGHT},
                             {"Update flight", UPDATE_FLIGHT},
                             {"Delete flight", DELETE_FLIGHT}});
}

void UserInterface::clientsMenu(Company &comp) {
    std::stringstream text;
    text << "These are all the clients:\n\n";

    for (const Client &client : comp.getClients()) {
        text << client.getNIF() << '\t' << client.getName() << '\n';
    }

    text << "\nChoose an operation...";

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New client", CREATE_CLIENT},
                             {"Client info", READ_CLIENT},
                             {"Update client", UPDATE_CLIENT},
                             {"Delete client", DELETE_CLIENT}});
}

void UserInterface::updateClient(Company &comp) {
    std::string strNIF, newName, newNIF;
    std::cout << "Insert the NIF of the client you wish to update: "
              << std::flush;
    getInput(strNIF);
    for (Client c : comp.getClients()) {
        if (stoul(strNIF) == c.getNIF()) {
            std::cout << "Current name: " << c.getName() << '\n'
                      << "New name (press Enter to not alter the current one): "
                      << std::flush;
            getInput(newName);
            if (newName != "") {
                c.setName(newName);
            }

            std::cout << "Current NIF: " << strNIF << '\n'
                      << "New NIF (press Enter to not alter the current one): "
                      << std::flush;
            getInput(newNIF);
            if (newNIF != "") {
                c.setNIF(stoul(newNIF));
            }

            std::cout << "The changes have been saved!\n"
                      << "Returning to the previous menu..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            _currentMenu = CLIENTS;
        }
    }
    std::cout << "That client does not exist! Re-enter the NIF..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    _currentMenu = UPDATE_CLIENT;
}

void UserInterface::deleteClientMenu(Company &comp) {
    std::string strNIF, confirm;
    bool flag = true;
    std::cout << "Insert the NIF of the client you wish to delete: "
              << std::flush;
    getInput(strNIF);
    for (Client c : comp.getClients()) {
        if (stoul(strNIF) == c.getNIF()) {
            do {
                std::cout << "Confirm (Y/N): " << std::flush;
                getInput(confirm);
                if (confirm == "Y") {
                    std::cout << "Deleting..." << std::flush;
                    // AAAAAAAAAAAAAAAA COMO E Q SE DA DELETE DE UM VETOR MERDA
                    // FDS :doom:
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(1000));
                    std::cout << "Done! Returning to the previous menu..."
                              << std::flush;
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(1000));
                    flag = false;
                } else if (confirm == "N") {
                    std::cout << "Returning to the previous menu..."
                              << std::flush;
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(2000));
                    flag = false;
                }
            } while (flag);
            _currentMenu = CLIENTS;
        }
    }
    std::cout << "That client does not exist! Re-enter the NIF..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    _currentMenu = DELETE_CLIENT;
}

void UserInterface::createClientMenu(Company &comp) {
    std::string name, strNIF;
    unsigned NIF;

    std::cout << "Insert the client's name: " << std::flush;

    getInput(name);

    std::cout << "Insert the client's NIF: " << std::flush;

    getInput(strNIF);

    if (isDigitOnly(strNIF)) {
        NIF = stoul(strNIF);
        std::cout << "\nCreating the client..." << std::flush;
        Client client = Client(name, NIF);
        comp.addClient(client);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Created client: " << name << " - " << strNIF << std::endl;
        std::cout << "Returning to the previous menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _currentMenu = CLIENTS;
    } else {
        std::cout << "An error has occurred! Re-enter the data..."
                  << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _currentMenu = CREATE_CLIENT;
    }
}

void showFlights(Client &client, Company &comp) {
    for (auto ticket : client.getTickets()) {
        Flight *f = comp.findFlight(ticket.getFlightID());

        std::cout << "Ticket: " << ticket.getID() << '\n'
                  << "Flight Number:" << f->getNumber() << '\n'
                  << "From->To:" << f->getOrigin() << "->"
                  << f->getDestination() << '\n'
                  << "Date of Departure: " << f->getDepartureDate() << '\n'
                  << "---------------------" << std::endl;
    }
}

void UserInterface::readClientMenu(Company &comp) {
    Client *client;
    std::string strNIF, back;
    std::cout << "Insert the client's NIF: " << std::flush;
    getInput(strNIF);

    if (client = comp.findClient(stoul(strNIF))) {
        std::cout << "Name: " << client->getName() << '\n'
                  << "NIF: " << client->getNIF() << "\nFlights:" << std::endl;
        showFlights(*client, comp);

        std::cout << "Press 0 to go back!" << std::endl;
        getInput(back);
        if (back == "0") {
            _currentMenu = CLIENTS;
        }
    } else {
        std::cout << "That client does not exist! Re-enter the NIF..."
                  << std::endl;
        _currentMenu = READ_CLIENT;
    }
}

void UserInterface::clientsFlightsMenu(Company &comp) {
    std::string back;
    showFlights(*currClient, comp);
    std::cout << "Press 0 to go back!" << std::endl;
    getInput(back);
    if (back == "0") {
        _currentMenu = CLIENT_OPTIONS;
    }
}

void UserInterface::show(Company &comp) {
    // TODO: rename clientMenu() and clientsMenu()
    switch (_currentMenu) {
    case CLIENT:
        clientMenu(comp);
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
    case CREATE_CLIENT:
        createClientMenu(comp);
        break;
    case READ_CLIENT:
        readClientMenu(comp);
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
