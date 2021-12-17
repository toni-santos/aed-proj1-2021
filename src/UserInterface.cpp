#include "../includes/UserInterface.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <thread>

// TODO: IMPLEMENT WRITE/DELETE
// TODO: WHEN PRINNTING AIRPORTS PRINT THE NEARBY DESTINATIONS (?)
// TODO: DESTINATIONS
// TODO: TICKETS THAT ARE BOUGHT ARE NOT SAVING THAT INFORMATION (aka Client attribute)
// TODO: IMPLEMENT CHECKING IF SEAT IS OCCUPIED WHEN BUYING TICKETS (fix above first obvs)
// TODO: SEGFAULT WHEN BUYING MULTIPLE TICKETS
// TODO: UPDATE OF CARTS

void printServiceList(Company &comp) {
    for (auto plane : comp.getPlanes()) {
        std::cout << "Type - Date - Worker" << std::endl;
        printPlaneServices(plane);
    }
}

void printPlaneServices(Plane *plane) {
    unsigned cnt{0};

    if (plane->getServices().size() == 0) {
        std::cout << "No services to be done!\n";
    } else {
        for (const Service &service : plane->getServices()) {
            std::cout << cnt << service.getType() << " - "
                      << service.getWorker() << " - " << service.getDate()
                      << '\n';
        }
    }
    std::cout << std::endl;

    cnt = 0;

    if (plane->getServicesDone().size() == 0) {
        std::cout << "No services have been done!\n";
    } else {
        for (const Service &service : plane->getServicesDone()) {
            std::cout << cnt << service.getType() << " - "
                      << service.getWorker() << " - " << service.getDate()
                      << '\n'
                      << std::flush;
        }
    }
    std::cout << std::endl;
}

void printPlaneVector(std::vector<Plane *> sortedVec) {
    std::cout << "ID - Type - Plate - Capacity - Flight IDs\n\n" << std::flush;
    for (const Plane *plane : sortedVec) {
        std::string fls = " - ";
        std::list<Flight *> temp = plane->getFlights();
        for (auto f : temp) {
            fls += std::to_string(f->getID()) + " ";
        }
        std::cout << plane->getID() << " - " << plane->getType() << " - "
                  << plane->getPlate() << " - " << plane->getCapacity() << fls
                  << std::endl;
    }
}

void printClientFlights(Client *client, Company &comp) {
    std::cout << "\nTicket - Flight Number - Origin->Destination - Date of Departure\n\n";
    for (auto ticket : client->getTickets()) {
        const Flight *f = ticket->getFlight();

        std::cout << f->getPlane()->getID()  << " - "
                  << f->getNumber() << " - "
                  << f->getOrigin()->getName() << "->"
                  << f->getDestination()->getName() << " - "
                  << f->getDepartureDate()
                  << "\n---------------------" << std::endl;
    }
}

void printClientVector(std::vector<Client *> sortedVec, Company &comp) {
    for (Client *client : sortedVec) {
        std::cout << "Name: " << client->getName() << '\n'
                  << "NIF: " << client->getNIF() << "\nFlights:" << std::endl;
        printClientFlights(client, comp);
    }
}

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

unsigned UserInterface::getNumberInput(std::string prompt, unsigned min,
                                       unsigned max) {
    std::string input;
    unsigned number;
    bool done = false;

    do {
        std::cout << ERROR_MESSAGE << _errorMessage << RESET_FORMATTING;
        _errorMessage = "";
        std::cout << prompt;
        getInput(input);

        try {
            number = stoul(input);
            done = true;
        } catch (std::invalid_argument) {
            _errorMessage = "Invalid input!\n";
            done = false;
        }
    } while (!done || !inRange(number, min, max));

    return number;
}

bool UserInterface::inRange(unsigned n, unsigned min, unsigned max) {
    bool b = (n <= max) && (n >= min);

    if (!b)
        _errorMessage = "Value outside allowed range!\n";

    return b;
}

bool validCredentials(std::string &username, std::string &password) {
    return username == "admin" && password == "admin";
}

bool isDigitOnly(std::string strNIF) {
    return std::all_of(strNIF.begin(), strNIF.end(),
                       [](char c) { return std::isdigit(c); });
}

void UserInterface::clientMenu(Company &comp) {
    std::string name;

    std::cout << CLEAR_SCREEN << "Welcome to " << COMPANY_NAME << std::endl;
    unsigned userNIF = getNumberInput("Please enter your NIF: ");

    for (Client *c : comp.getClients()) {
        if (c->getNIF() == userNIF) {
            currClient = c;
            loadString("Connecting you to our services...", 3000);
            _currentMenu = CLIENT_OPTIONS;
            return;
        }
    }

    std::cout << "It seems you have never travelled with us... :(\n"
              << "To finish your registration insert your name: " << std::flush;

    getInput(name);

    currClient = comp.createClient(userNIF, name);
    std::cout << "Thanks for choosing " << COMPANY_NAME << std::endl;
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
    optionsMenu(COMPANY_NAME,
                {{"Exit", EXIT}, {"Client", CLIENT}, {"Employee", EMPLOYEE}});
}

void UserInterface::employeeOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - ADMIN", {{"Log off", MAIN},
                                            {"Planes", PLANES},
                                            {"Flights", FLIGHTS},
                                            {"Services", SERVICES},
                                            {"Airports", AIRPORTS},
                                            {"Clients", CLIENTS}});
}

void UserInterface::clientOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Welcome " + currClient->getName() + "!",
                {{"Go back", MAIN},
                 {"Check my flights", CHECK_FLIGHTS},
                 {"Buy tickets", BUY_TICKETS}});
}

void UserInterface::servicesMenu(Company &comp) {
    std::stringstream text;
    std::string p;

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New service", CREATE_SERVICE},
                             {"Check services", READ_SERVICE},
                             {"Do service", COMPLETE_SERVICE}});
}

void UserInterface::planesMenu(Company &comp) {
    std::stringstream text;

    std::cout << "PLANES\n" << std::endl;

    std::cout << "Choose an operation..." << std::endl;

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New plane", CREATE_PLANE},
                             {"Plane info", READ_PLANE},
                             {"Update plane", UPDATE_PLANE},
                             {"Delete plane", DELETE_PLANE}});
}

void UserInterface::completeService(Company &comp) {
    unsigned planeID, sID;
    printPlaneVector(comp.getPlanes());

    planeID = getNumberInput("Insert the ID of the plane: ", 0,
                             comp.getPlanes().size() - 1);

    comp.getPlanes().at(planeID)->doService();

    std::cout << "Service done... Returning to the previous menu..."
              << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    _currentMenu = SERVICES;
}

void UserInterface::createPlane(Company &comp) {
    std::string plate, type;
    unsigned rows, cols;

    std::cout << "Insert the plane's plate: " << std::flush;
    getInput(plate);

    std::cout << "Insert the plane's type: " << std::flush;
    getInput(type);

    rows = getNumberInput("Insert the plane's rows (max. 26): ", 1, 26);

    cols = getNumberInput("Insert the plane's columns: ", 1);

    std::cout << "\nCreating the plane..." << std::flush;
    comp.createPlane(rows, cols, plate, type);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Returning to the previous menu..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    _currentMenu = PLANES;
}

void UserInterface::checkPlane(Company &comp) {
    std::string opt;

    std::cout << "ID:       (1) Descending	(q) Ascending\n"
              << "Type:     (2) Descending	(w) Ascending\n"
              << "Plate:    (3) Descending	(e) Ascending\n"
              << "Capacity: (4) Descending	(r) Ascending\n"
              << "(0) Go back" << std::endl;

    std::cout << ERROR_MESSAGE << _errorMessage << RESET_FORMATTING;
    _errorMessage = "";
    std::cout << "Choose an ordering strategy..." << std::endl;
    getInput(opt);

    if (opt == "1") {
        std::vector<Plane *> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getID() > p2->getID();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "q") {
        std::vector<Plane *> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getID() < p2->getID();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "2") {
        std::stringstream text;

        std::vector<Plane *> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getType() > p2->getType();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "w") {
        std::stringstream text;

        std::vector<Plane *> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getType() < p2->getType();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "3") {
        std::stringstream text;

        std::vector<Plane *> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getPlate() > p2->getPlate();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "e") {
        std::stringstream text;

        std::vector<Plane *> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getPlate() < p2->getPlate();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "4") {
        std::stringstream text;

        std::vector<Plane *> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getCapacity() > p2->getCapacity();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "r") {
        std::stringstream text;

        std::vector<Plane *> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getCapacity() < p2->getCapacity();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "0") {
        std::cout << "Returning to the previous menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = PLANES;

    } else {
        _errorMessage = "Invalid input!\n";
    }
}

void UserInterface::updatePlane(Company &comp) {
    unsigned id, newRows, newCols;
    Plane *plane;

    while (true) {
        id =
            getNumberInput("Insert the ID of the plane you wish to update: ", 0,
                           comp.getPlanes().size() - 1);

        if (plane = comp.getPlanes().at(id))
            break;
        else
            _errorMessage = "Invalid input!\n";
    }

    std::cout << "Current rows: " << plane->getRows() << '\n';
    newRows = getNumberInput("New rows (0 to keep current value): ", 0, 26);

    std::cout << "Current columns: " << plane->getColumns() << '\n';
    newCols = getNumberInput("New columns (0 to keep current value): ", 0, 99);

    comp.updatePlane(plane, newRows, newCols);

    std::cout << "The changes have been saved!\n"
              << "Returning to the previous menu..." << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    _currentMenu = PLANES;
}

void UserInterface::deletePlane(Company &comp) {
    std::string confirm;
    unsigned id;
    Plane *plane;

    while (true) {
        id =
            getNumberInput("Insert the ID of the plane you wish to delete: ", 0,
                           comp.getPlanes().size() - 1);

        if (plane = comp.getPlanes().at(id))
            break;
        else
            _errorMessage = "Invalid input!\n";
    }

    std::cout << "Confirm (y/N): " << std::flush;
    getInput(confirm);
    if (confirm == "Y" || confirm == "y") {
        comp.deletePlane(plane);
        std::cout << "Deleting..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Done! Returning to the previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } else {
        std::cout << "Returning to the previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    _currentMenu = PLANES;
}

void UserInterface::flightsMenu(Company &comp) {
    std::stringstream text;
    text << "These are all the flights:\n\n";
    text << "Number - Departure Date - Origin->Destination - Duration\n\n";
    for (Flight *flight : comp.getFlights()) {
        text << flight->getNumber() << " - " << flight->getDepartureDate()
             << " - " << flight->getOrigin()->getName() << "->"
             << flight->getDestination()->getName() << " - "
             << flight->getDuration() << '\n';
    }

    text << "\nChoose an operation...";

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New flight", CREATE_FLIGHT},
                             {"Check flight", READ_FLIGHT},
                             {"Update flight", UPDATE_FLIGHT},
                             {"Delete flight", DELETE_FLIGHT}});
}

void UserInterface::createFlight(Company &comp) {
    std::string origin, dest, departureDate;
    unsigned planeID, number, duration;

    Airport *o;
    Airport *d;

    number = getNumberInput("Insert the flight number: ");

    duration = getNumberInput("Insert the flight duration: ");

    std::cout << "Insert the flight origin: " << std::flush;
    getInput(origin);

    std::cout << "Insert the flight destination: " << std::flush;
    getInput(dest);

    std::cout << "Insert the flight departure date: " << std::flush;
    getInput(departureDate);

    planeID = getNumberInput("Insert the flight's plane number: ", 0,
                             comp.getPlanes().size() - 1);

    if (comp.findAirport(origin) != nullptr) {
        o = comp.createAirport(origin);
    } else {
        o = comp.findAirport(origin);
    }

    if (comp.findAirport(dest) != nullptr) {
        d = comp.createAirport(dest);
    } else {
        d = comp.findAirport(dest);
    }

    if (comp.findPlane(planeID) == nullptr) {
        std::cout << "That is not a valid plane! Please retry..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = CREATE_FLIGHT;
    } else {
        comp.createFlight(number, duration, o, d, departureDate,
                          comp.findPlane(planeID));
        std::cout << "Creating flight..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Done! Returning to previous menu!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = FLIGHTS;
    }
}

void printAirportVector(Company &comp) {
    std::cout << "ID - Name\n";
    for (auto a : comp.getAirports()) {
        std::cout << a->getID() << " - " << a->getName() << '\n' << std::flush;
    }
}

void printFlightVector(std::vector<Flight *> sortedVec) {
    for (Flight *flight : sortedVec) {
        std::cout << flight->getNumber() << " - "
                  << flight->getOrigin()->getName() << "->"
                  << flight->getDestination()->getName() << " - "
                  << flight->getDepartureDate() << " - "
                  << flight->getDuration() << " - "
                  << flight->getPlane()->getID() << std::endl;
    }
}

void UserInterface::readFlight(Company &comp) {
    std::string opt;
    std::cout << "Choose an ordering strategy..." << std::endl;

    std::cout << "Flight Number: (1) Descending	(q) Ascending" << std::endl;
    std::cout << "Duration: (2) Descending	(w) Ascending" << std::endl;
    std::cout << "Plane ID: (3) Descending	(e) Ascending" << std::endl;
    std::cout << "(0) Go back" << std::endl;
    getInput(opt);

    std::cout << "Flight Number - Origin->Destination - Departure Date - "
                 "Duration - Plane ID\n"
              << std::flush;
    if (opt == "1") {
        std::vector<Flight *> sortedVec = comp.getFlights();
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Flight *p1, Flight *p2) { return p1->getID() > p2->getID(); });

        printFlightVector(sortedVec);

    } else if (opt == "q") {
        std::vector<Flight *> sortedVec = comp.getFlights();
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Flight *p1, Flight *p2) { return p1->getID() < p2->getID(); });

        printFlightVector(sortedVec);

    } else if (opt == "2") {
        std::vector<Flight *> sortedVec = comp.getFlights();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Flight *p1, Flight *p2) {
                      return p1->getDuration() > p2->getDuration();
                  });

        printFlightVector(sortedVec);

    } else if (opt == "w") {
        std::vector<Flight *> sortedVec = comp.getFlights();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Flight *p1, Flight *p2) {
                      return p1->getDuration() < p2->getDuration();
                  });

        printFlightVector(sortedVec);

    } else if (opt == "3") {
        std::vector<Flight *> sortedVec = comp.getFlights();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Flight *p1, Flight *p2) {
                      return p1->getPlane()->getID() > p2->getPlane()->getID();
                  });

        printFlightVector(sortedVec);

    } else if (opt == "e") {
        std::vector<Flight *> sortedVec = comp.getFlights();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Flight *p1, Flight *p2) {
                      return p1->getPlane()->getID() < p2->getPlane()->getID();
                  });

        printFlightVector(sortedVec);

    } else if (opt == "0") {
        std::cout << "Returning to the previous menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = FLIGHTS;
    } else {
        std::cout << "That's not a valid input! Please choose a valid one..."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = READ_PLANE;
    }
}

void UserInterface::updateFlight(Company &comp) {
    std::string newDeparture;
    unsigned ID, newPlaneID, newDuration, newOrigin, newDest;
    bool flag = true;
    ID = getNumberInput(
        "Insert the flight ID of the flight you wish to update: ");
    for (Flight *flight : comp.getFlights()) {
        if (ID == flight->getID()) {
            std::cout << "Current duration: " << flight->getDuration() << '\n'
                      << std::flush;
            newDuration = getNumberInput(
                "New duration (press Enter to not alter the current one): ", 1);

            printAirportVector(comp);

            std::cout << "Current origin: " << flight->getOrigin()->getName()
                      << '\n'
                      << std::flush;
            newOrigin = getNumberInput(
                "New origin ID (press Enter to not alter the current one): ");

            printAirportVector(comp);

            std::cout << "Current destination: "
                      << flight->getDestination()->getName() << '\n'
                      << std::flush;
            newDest = getNumberInput("New destination ID (press Enter to not "
                                     "alter the current one): ");

            std::cout << "Current departure date: "
                      << flight->getDepartureDate() << '\n'
                      << "New departure date (press Enter to not alter the "
                         "current one): "
                      << std::flush;
            getInput(newDeparture);

            std::cout << "Current plane ID: " << flight->getPlane()->getID()
                      << '\n'
                      << std::flush;
            newPlaneID = getNumberInput(
                "New plane ID (press Enter to not alter the current one): ");

            comp.updateFlight(flight, newDuration, newOrigin, newDest,
                              newDeparture, newPlaneID);

            std::cout << "The changes have been saved!\n"
                      << "Returning to the previous menu..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            flag = false;
        }
    }
    if (flag) {
        std::cout << "That flight does not exist! Re-enter the flight ID..."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = UPDATE_FLIGHT;
    } else {
        _currentMenu = FLIGHTS;
    }
}

void UserInterface::removeFlight(Company &comp) {
    std::string confirm;
    unsigned id;
    Flight *flight;

    while (true) {
        id = getNumberInput(
            "Insert the flight ID of the flight you wish to delete: ", 0,
            comp.getFlights().size() - 1);

        if (flight = comp.getFlights().at(id))
            break;
        else
            _errorMessage = "Invalid input!\n";
    }

    std::cout << "Confirm (y/N): " << std::flush;
    getInput(confirm);
    if (confirm == "Y" || confirm == "y") {
        comp.deleteFlight(flight);
        std::cout << "Deleting... " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Done! Returning to the previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } else {
        std::cout << "Returning to the previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    _currentMenu = FLIGHTS;
}

void UserInterface::clientsMenu(Company &comp) {
    std::stringstream text;
    text << "These are all the clients:\n\n";

    for (const Client *client : comp.getClients()) {
        text << client->getNIF() << '\t' << client->getName() << '\n';
    }

    text << "\nChoose an operation...";

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New client", CREATE_CLIENT},
                             {"Client info", READ_CLIENT},
                             {"Update client", UPDATE_CLIENT},
                             {"Delete client", DELETE_CLIENT}});
}

void UserInterface::updateClientMenu(Company &comp) {
    std::string strNIF, newName;
    bool flag = true;
    strNIF =
        getNumberInput("Insert the NIF of the client you wish to update: ");
    for (Client *client : comp.getClients()) {
        std::cout << "Current name: " << client->getName() << '\n'
                  << "New name (press Enter to not alter the current one): "
                  << std::flush;
        getInput(newName);

        comp.updateClient(client, newName);

        std::cout << "The changes have been saved!\n"
                  << "Returning to the previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        flag = false;
    }
    if (flag) {
        std::cout << "That client does not exist! Re-enter the NIF..."
                  << std::endl;
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
    for (Client *client : comp.getClients()) {
        strNIF =
            getNumberInput("Insert the NIF of the client you wish to delete: ");
        do {
            std::cout << "Confirm (y/N): " << std::flush;
            getInput(confirm);
            if (confirm == "Y" || confirm == "y") {
                flag = false;
                comp.deleteClient(client);
                std::cout << "Deleting..." << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "Done! Returning to the previous menu..."
                          << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            } else {
                std::cout << "Returning to the previous menu..." << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                flag = false;
            }
        } while (flag);
        break;
    }
    if (flag) {
        std::cout << "That client does not exist! Re-enter the NIF..."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = DELETE_CLIENT;
    } else {
        _currentMenu = CLIENTS;
    }
}

void UserInterface::createClientMenu(Company &comp) {
    std::string name;
    unsigned NIF;

    std::cout << "Insert the client's name: " << std::flush;

    getInput(name);

    NIF = getNumberInput("Insert the client's NIF: ");
    if (!comp.findClient(NIF)) {
        std::cout << "\nCreating the client..." << std::flush;
        comp.createClient(NIF, name);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Created client: " << name << " - " << std::to_string(NIF)
                  << std::endl;
        std::cout << "Returning to the previous menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _currentMenu = CLIENTS;
    } else {
        std::cout << "There was an error creating the client!\nReturning to "
                     "the previous menu..."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _currentMenu = CLIENTS;
    }
}

void UserInterface::readClientMenu(Company &comp) {
    std::string opt;

    std::cout << "NIF: (1) Descending	(q) Ascending" << std::endl;
    std::cout << "Name: (2) Descending	(w) Ascending" << std::endl;
    std::cout << "(0) Go back..." << std::endl;
    getInput(opt);

    if (opt == "1") {
        std::vector<Client *> sortedVec = comp.getClients();
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Client *c1, Client *c2) { return c1->getNIF() > c2->getNIF(); });

        printClientVector(sortedVec, comp);

    } else if (opt == "q") {
        std::vector<Client *> sortedVec = comp.getClients();
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Client *c1, Client *c2) { return c1->getNIF() < c2->getNIF(); });

        printClientVector(sortedVec, comp);

    } else if (opt == "2") {
        std::vector<Client *> sortedVec = comp.getClients();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Client *c1, Client *c2) {
                      return c1->getName() > c2->getName();
                  });

        printClientVector(sortedVec, comp);

    } else if (opt == "w") {
        std::vector<Client *> sortedVec = comp.getClients();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Client *c1, Client *c2) {
                      return c1->getName() < c2->getName();
                  });

        printClientVector(sortedVec, comp);

    } else if (opt == "0") {
        std::cout << "Returning to the previous menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = CLIENTS;
    } else {
        std::cout << "That's not a valid input! Please choose a valid one..."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = READ_CLIENT;
    }
}

void UserInterface::clientsFlightsMenu(Company &comp) {
    std::string back;
    printClientFlights(currClient, comp);
    std::cout << "Press 0 to go back!" << std::endl;
    getInput(back);
    if (back == "0") {
        _currentMenu = CLIENT_OPTIONS;
    }
}

void UserInterface::createService(Company &comp) {
    std::string date, worker;
    unsigned int type;
    unsigned planeID;

    getNumberInput(
        "(0) Cleaning\n(1) Maintenance\n\nInsert the service's type: ", 0, 1);

    std::cout << "Insert the service's responsible worker: " << std::flush;

    getInput(worker);

    std::cout << "Insert the service's date (DD/MM/YY): " << std::flush;

    getInput(date);

    planeID = getNumberInput(
        "Insert the id of the plane that will receive this service: ", 0,
        comp.getPlanes().size() - 1);

    Service service = Service(static_cast<ServiceType>(type), date, worker);
    comp.getPlanes().at(planeID)->addService(service);

    std::cout << "Service has been created! Returning to previous menu..."
              << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    _currentMenu = SERVICES;
}

void UserInterface::readService(Company &comp) {
    std::string back;
    printServiceList(comp);
    std::cout << "Press 0 to go back!" << std::endl;
    getInput(back);
    if (back == "0") {
        _currentMenu = SERVICES;
    }
}

void printPlaneLayout(Flight *flight) {
    Plane *plane = flight->getPlane();
    unsigned rows = plane->getRows();
    unsigned columns = plane->getColumns();
    unsigned width = numberLength(columns);

    for (int j = width - 1; j >= 0; j--) {
        std::cout << "  ";
        for (unsigned i = 1; i <= columns; i++) {
            std::cout << i / ((unsigned)pow(10, j)) % 10;
        }
        std::cout << '\n';
    }

    for (unsigned row = 0; row < rows; ++row) {
        printf("%c ", 'A' + row);
        std::cout << " ";
        for (unsigned column = 0; column < columns; ++column) {
            Ticket *ticket = flight->getTickets().at(row * columns + column);

            std::cout << (ticket->getClient() ? "x" : "o");
        }

        std::cout << std::endl;
    }
}

void UserInterface::clientBuyTickets(Company &comp) {
    std::string seat, name, opt2;
    unsigned opt, opt1, NIF;

    std::cout << "Available flights: \n" << std::flush;
    std::cout << "Flight Number - Origin->Destination - Departure Date - "
                 "Duration - Plane ID\n\n"
              << std::flush;
    printFlightVector(comp.getFlights());

    opt = getNumberInput("\nChoose a flight number to buy tickets: ");

    if (opt == 0) {
        std::cout << "Returning to previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = CLIENT_OPTIONS;
    }

    Flight *flight = comp.findFlight(opt);

    if (flight->getAvailability() > 0) {
        opt1 = getNumberInput(
            "Will you be travelling alone or in a group (0/1 = alone)? ");

        if (opt1 == 0 || opt == 1) {
            printPlaneLayout(flight);
            std::cout << "Pick a seat: " << std::flush;
            getInput(seat);

            if (flight->findTicketBySeat(seat) != nullptr) {
                std::cout << "Do you wish to use automatic "
                             "luggaging? (y/N) "
                          << std::flush;
                getInput(opt2);
                if (opt2 == "Y" || opt2 == "y") {
                    doLuggaging(comp, flight, currClient->getNIF(), seat);
                    _currentMenu = CLIENT_OPTIONS;
                } else {
                    comp.findClient(currClient->getNIF())->addTicket(
                                flight->findTicketBySeat(seat));
                        std::cout << "The ticket has been purchased! "
                                  << "Thanks for travelling with us... :D\n"
                                  << std::flush;
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        _currentMenu = CLIENT_OPTIONS;
                    }

                } else {
                std::cout << "That's not a valid seat! "
                          << "Returning to previous menu..." << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                _currentMenu = CLIENT_OPTIONS;
            }
        } else {
            if (opt1 <= flight->getAvailability()) {
                for (int i = 0; i < opt1; i++) {
                    NIF = getNumberInput("Insert the passenger's NIF: ");

                    if (comp.findClient(NIF) != nullptr) {
                        printPlaneLayout(flight);
                        std::cout << "Pick a seat: " << std::flush;
                        getInput(seat);
                        if (flight->findTicketBySeat(seat) != nullptr) {
                            std::cout << "Do you wish to use automatic "
                                         "luggaging? (y/N) "
                                      << std::flush;
                            getInput(opt2);

                            if (opt2 == "Y" || opt2 == "y") {
                                doLuggaging(comp, flight, NIF, seat);
                            } else {
                                comp.findClient(NIF)->addTicket(
                                        flight->findTicketBySeat(seat));
                                std::cout << "The ticket has been purchased! "
                                          << "Thanks for travelling with us... :D\n"
                                          << std::flush;
                                std::this_thread::sleep_for(
                                        std::chrono::milliseconds(1000));
                            }
                        } else {
                                std::cout << "That's not a valid seat! "
                                          << "Returning to previous menu..."
                                          << std::flush;
                                std::this_thread::sleep_for(
                                        std::chrono::milliseconds(1000));
                                _currentMenu = CLIENT_OPTIONS;
                        }
                    } else {
                        std::cout << "It seems you have never "
                                     "travelled with us... :(\n"
                                  << "To finish your registration "
                                     "insert your name: "
                                  << std::flush;

                        getInput(name);

                        if (NIF) {
                            comp.createClient(NIF, name);
                        }
                        std::cout << "\n\n";

                        printPlaneLayout(flight);
                        std::cout << "Pick a seat: " << std::flush;
                        getInput(seat);
                        if (flight->findTicketBySeat(seat) != nullptr) {
                            comp.findClient(NIF)->addTicket(
                                flight->findTicketBySeat(seat));
                        } else {
                            std::cout << "That's not a valid seat! "
                                      << "Returning to previous menu..."
                                      << std::flush;
                            std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                            _currentMenu = CLIENT_OPTIONS;
                        }
                    }
                }
                _currentMenu = CLIENT_OPTIONS;
            } else {
                std::cout << "Not enough seats left on that plane! "
                          << "Returning to previous menu..." << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                _currentMenu = CLIENT_OPTIONS;
            }
        }
    } else {
        std::cout
            << "It seems there are no available tickets for this flight!\n"
            << std::flush;
        std::cout << "Returning to previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = CLIENT_OPTIONS;
    }
}

void UserInterface::airportsMenu(Company &comp) {
    std::stringstream text;

    std::cout << "AIRPORTS\n" << std::endl;

    std::cout << "Choose an operation..." << std::endl;

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New airport", CREATE_AIRPORT},
                             {"Check airports", READ_AIRPORT},
                             {"Remove airport", DELETE_AIRPORT}});
}

void UserInterface::doLuggaging(Company &comp, Flight *flight, unsigned NIF, std::string seat) {
    // TODO: SEGFAULT AQUI DENTRO
    Luggage *luggage =
            new Luggage(comp.findClient(NIF));
    flight->findTicketBySeat(seat)->addLuggage(
            luggage);
    comp.findCart(flight->getID())
            ->addLuggage(luggage);
    comp.findClient(NIF)->addTicket(
            flight->findTicketBySeat(seat));
    std::cout << "The ticket has been purchased "
                 "and your luggage will be taken "
                 "care by our team! "
              << "Thanks for travelling with us... :D\n"
              << std::flush;
    std::this_thread::sleep_for(
            std::chrono::milliseconds(1000));
}

void UserInterface::createAirport(Company &comp) {
    std::string name;

    std::cout << "Insert the name of the airport: " << std::flush;
    getInput(name);

    if (comp.findAirport(name) == nullptr) {
        comp.createAirport(name);
        std::cout << "Creating airport..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Done! Returning to previous menu!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = AIRPORTS;
    } else {
        std::cout << "That airport already exists! Please retry..."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = CREATE_AIRPORT;
    }
}

void UserInterface::readAirport(Company &comp) {
    std::string back;
    printAirportVector(comp);
    std::cout << "Press 0 to go back!" << std::endl;
    getInput(back);
    if (back == "0") {
        _currentMenu = AIRPORTS;
    }
}

void UserInterface::deleteAirport(Company &comp) {
    std::string confirm;
    unsigned id;
    Airport *airport;
    printAirportVector(comp);
    while (true) {
        id = getNumberInput(
            "Insert the  ID of the airport you wish to delete: ", 0,
            comp.getAirports().size() - 1);

        if (airport = comp.getAirports().at(id))
            break;
        else
            _errorMessage = "Invalid input!\n";
    }

    std::cout << "Confirm (y/N): " << std::flush;
    getInput(confirm);

    if (confirm == "Y" || confirm == "y") {
        comp.deleteAirport(airport);
        std::cout << "Deleting... " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Done! Returning to the previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = AIRPORTS;
    } else {
        std::cout << "Returning to the previous menu..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _currentMenu = AIRPORTS;
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
    case BUY_TICKETS:
        clientBuyTickets(comp);
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
        createFlight(comp);
        break;
    case UPDATE_FLIGHT:
        updateFlight(comp);
        break;
    case DELETE_FLIGHT:
        removeFlight(comp);
        break;
    case READ_FLIGHT:
        readFlight(comp);
        break;
    case SERVICES:
        servicesMenu(comp);
        break;
    case CREATE_SERVICE:
        createService(comp);
        break;
    case COMPLETE_SERVICE:
        completeService(comp);
        break;
    case READ_SERVICE:
        readService(comp);
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
    case AIRPORTS:
        airportsMenu(comp);
        break;
    case CREATE_AIRPORT:
        createAirport(comp);
        break;
    case DELETE_AIRPORT:
        deleteAirport(comp);
        break;
    case READ_AIRPORT:
        readAirport(comp);
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
    loadString("Shutting down...", 1000);
}
