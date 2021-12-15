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
        text << plane.getID() << '\n';
    }

    text << "\nChoose a plane...";
    getInput(p);

    for (const Plane &plane : comp.getPlanes()) {
        if (stoul(p) == plane.getID()) {
            optionsMenu(text.str(), {{"Go back", SERVICES},
                                     {"New service", CREATE_SERVICE},
                                     {"Check services", READ_SERVICE},
                                     {"Update service", UPDATE_SERVICE},
                                     {"Delete service", DELETE_SERVICE}});
        }
    }
}

void UserInterface::planesMenu(Company &comp) {
    std::stringstream text;
    text << "These are all the planes:\n\n";
    text << "ID - Type - Plate - Capacity - Flights\n\n";
    for (const Plane &plane : comp.getPlanes()) {
        std::string fls;
        std::queue<unsigned> tempq = plane.getFlights();
        while (tempq.size() != 0) {
            fls += " " + std::to_string(tempq.front());
            tempq.pop();
        }

        text << plane.getID() << " - " << plane.getType() << " - "
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
    unsigned id;
    bool flag = true;

    std::cout << "Insert the plane's plate: " << std::flush;
    getInput(plate);

    std::cout << "Insert the plane's type: " << std::flush;
    getInput(type);

    std::cout << "Insert the plane's capacity: " << std::flush;
    getInput(strCapacity);

    std::cout << "Insert the plane's ID: " << std::flush;
    getInput(strId);


    // TODO: check if id doesnt exist I WONDER IF THAT WOULD BE EASIER WITH
    // ANOTHER TOOL HAHA MAYBE SQL OR SOME SORT OF DB LANGUAGE HAHA OH WELL
    // THATS JUST ME IM QUIRKY LIKE THAT XD
    for (auto p: comp.getPlanes()) {
        if (stoul(strId) == p.getID()) {
            std::cout << "A plane with that ID already exists! Re-enter the data..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            flag = false;
        }
    }
    if (flag) {
        if (isDigitOnly(strCapacity) && isDigitOnly(strId)) {
            std::cout << "\nCreating the plane..." << std::flush;
            Plane plane = Plane(plate, type, std::stoul(strCapacity), stoul(strId));
            comp.addPlane(plane);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Returning to the previous menu..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            _currentMenu = PLANES;
        }
    } else {
        _currentMenu = PLANES;
    }

}

void UserInterface::checkPlane(Company &comp) {
    std::string strId, back;
    std::cout << "Insert the plane's ID: " << std::flush;
    getInput(strId);

    for (const Plane &plane: comp.getPlanes()) {
        if (plane.getID() == stoul(strId)) {
            std::string fls;
            std::queue<unsigned> tempq = plane.getFlights();
            while (tempq.size() != 0) {
                fls += " " + std::to_string(tempq.front());
                tempq.pop();
            }
            std::cout << "ID - Type - Plate - Capacity - Flights\n\n" << std::flush;
            std::cout << plane.getID() << " - " << plane.getType() << " - "
                      << plane.getPlate() << " - " << plane.getCapacity() << " -" << fls
                      << std::endl;

            std::cout << "Press 0 to go back!" << std::endl;
            getInput(back);
            if (back == "0") {
                _currentMenu = PLANES;

            }
        }
    }
}

void UserInterface::updatePlane(Company &comp) {
    std::string strId, newPlate, newType, newCapacity, newId;
    bool flag = true;
    std::cout << "Insert the ID of the plane you wish to update: "
              << std::flush;
    getInput(strId);
    for (int i = 0; i < comp.getPlanes().size(); i++) {
        if (stoul(strId) == comp.getPlanes().at(i).getID()) {
            std::cout << "Current plate: " << comp.getPlanes().at(i).getPlate() << '\n'
                      << "New plate (press Enter to not alter the current one): "
                      << std::flush;
            getInput(newPlate);

            std::cout << "Current type: " << comp.getPlanes().at(i).getType() << '\n'
                      << "New type (press Enter to not alter the current one): "
                      << std::flush;
            getInput(newType);

            std::cout << "Current capacity: " << comp.getPlanes().at(i).getCapacity() << '\n'
                      << "New capacity (press Enter to not alter the current one): "
                      << std::flush;
            getInput(newCapacity);

            comp.updatePlaneInfo(i, newPlate, newType, newCapacity, newId);

            std::cout << "The changes have been saved!\n"
                      << "Returning to the previous menu..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            flag = false;
        }
    }
    if (flag) {
        std::cout << "That client does not exist! Re-enter the NIF..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = UPDATE_PLANE;
    } else {
        _currentMenu = PLANES;
    }
}

void UserInterface::deletePlane(Company &comp) {
    std::string strId, confirm;
    bool flag = true;
    std::cout << "Insert the ID of the plane you wish to delete: "
              << std::flush;
    getInput(strId);
    for (std::vector<Plane>::iterator itr = comp.getPlanes().begin(); itr != comp.getPlanes().end(); itr++) {
        if (stoul(strId)==itr->getID()){
            do {
                std::cout << "Confirm (Y/N): " << std::flush;
                getInput(confirm);
                if (confirm == "Y") {
                    flag = false;
                    comp.removePlane(itr);
                    itr++;
                    std::cout << "Deleting..." << std::flush;
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(1000));
                    std::cout << "Done! Returning to the previous menu..."
                              << std::flush;
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(1000));
                } else if (confirm == "N") {
                    std::cout << "Returning to the previous menu..."
                              << std::flush;
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(2000));
                    flag = false;
                }
            }while (flag);
            break;
        }
    }
    if (flag) {
        std::cout << "That plane does not exist! Re-enter the ID..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = DELETE_PLANE;
    } else {
        _currentMenu = PLANES;
    }
}

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

void UserInterface::updateClientMenu(Company &comp) {
    std::string strNIF, newName, newNIF;
    bool flag = true;
    std::cout << "Insert the NIF of the client you wish to update: "
              << std::flush;
    getInput(strNIF);
    for (int i = 0; i < comp.getClients().size(); i++) {
        if (stoul(strNIF) == comp.getClients().at(i).getNIF()) {
            std::cout << "Current name: " << comp.getClients().at(i).getName() << '\n'
                      << "New name (press Enter to not alter the current one): "
                      << std::flush;
            getInput(newName);

            std::cout << "Current NIF: " << strNIF << '\n'
                      << "New NIF (press Enter to not alter the current one): "
                      << std::flush;
            getInput(newNIF);

            comp.updateClientInfo(i, newName, newNIF);

            std::cout << "The changes have been saved!\n"
                      << "Returning to the previous menu..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            flag = false;
        }
    }
    if (flag) {
        std::cout << "That client does not exist! Re-enter the NIF..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = UPDATE_CLIENT;
    } else {
        _currentMenu = CLIENTS;
    }
}

void UserInterface::deleteClientMenu(Company &comp) {
    std::string strNIF, confirm;
    bool flag = true;
    std::cout << "Insert the NIF of the client you wish to delete: "
              << std::flush;
    getInput(strNIF);
    for (std::vector<Client>::iterator itr = comp.getClients().begin(); itr != comp.getClients().end(); itr++) {
        if (stoul(strNIF)==itr->getNIF()){
            do {
                std::cout << "Confirm (Y/N): " << std::flush;
                getInput(confirm);
                if (confirm == "Y") {
                    flag = false;
                    comp.removeClient(itr);
                    itr++;
                    std::cout << "Deleting..." << std::flush;
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(1000));
                    std::cout << "Done! Returning to the previous menu..."
                              << std::flush;
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(1000));
                } else if (confirm == "N") {
                    std::cout << "Returning to the previous menu..."
                              << std::flush;
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(2000));
                    flag = false;
                }
            }while (flag);
            break;
        }
    }
    if (flag) {
        std::cout << "That client does not exist! Re-enter the NIF..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = DELETE_CLIENT;
    } else {
        _currentMenu = CLIENTS;
    }
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
    case MAIN:
        mainMenu();
        break;
    case CLIENT:
        clientMenu(comp);
        break;
    case CLIENT_OPTIONS:
        clientOptionsMenu();
        break;
    case CHECK_FLIGHTS:
        clientsFlightsMenu(comp);
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
    case CREATE_CLIENT:
        createClientMenu(comp);
        break;
    case READ_CLIENT:
        readClientMenu(comp);
        break;
    case DELETE_CLIENT:
        deleteClientMenu(comp);
        break;
    case UPDATE_CLIENT:
        updateClientMenu(comp);
        break;
    case FLIGHTS:
        flightsMenu(comp);
        break;
    case CREATE_FLIGHT:
        //createFlight(comp);
        break;
    case UPDATE_FLIGHT:
        //updateFlight(comp);
        break;
    case DELETE_FLIGHT:
        //deleteFlight(comp);
        break;
    case READ_FLIGHT:
        //readFlight(comp);
        break;
    case SERVICES:
        servicesMenu(comp);
        break;
    case CREATE_SERVICE:
        //createService(comp);
        break;
    case UPDATE_SERVICE:
        //updateService(comp);
        break;
    case DELETE_SERVICE:
        //deleteService(comp);
        break;
    case READ_SERVICE:
        //readService(comp);
        break;
    case PLANES:
        planesMenu(comp);
        break;
    case CREATE_PLANE:
        createPlane(comp);
        break;
    case UPDATE_PLANE:
        updatePlane(comp);
        break;
    case DELETE_PLANE:
        deletePlane(comp);
        break;
    case READ_PLANE:
        checkPlane(comp);
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
