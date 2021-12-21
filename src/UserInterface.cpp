#include "../includes/UserInterface.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"

#include <algorithm>
#include <iostream>
#include <list>

void UserInterface::optionsMenu(
    const std::string &text,
    const std::vector<std::pair<std::string, Menu>> &options) {
    std::cout << CLEAR_SCREEN << text << "\n\n";

    for (int i{1}; i < options.size(); ++i) {
        std::cout << "(" << i << ") " << options.at(i).first << std::endl;
    }

    std::cout << "(0) " << options.front().first << "\n\n";

    unsigned option = getNumberInput("Please insert option: ");

    if (option < options.size())
        _currentMenu = options.at(option).second;
    else
        _errorMessage = "Invalid option!\n";
}

void UserInterface::loadString(const std::string &text, unsigned time) const {
    unsigned inc = time / (text.size());

#ifdef NO_ANSI
    for (char c : text) {
        std::cout << c << std::flush;
        sleep(inc);
    }
#else
    std::cout << " ✈" << std::flush;
    for (char c : text) {
        std::cout << "\33[2D" << c << " ✈" << std::flush;
        sleep(inc);
    }
#endif

    std::cout << std::endl;
}

std::string UserInterface::getInput(std::string prompt) {
    std::cout << RED_TEXT << _errorMessage << RESET_FORMATTING << prompt;
    _errorMessage = "";

    std::string input{};

    std::getline(std::cin, input);
    normalizeInput(input);

    if (std::cin.eof())
        throw Exit();

    return input;
}

unsigned UserInterface::getNumberInput(std::string prompt, long min, long max) {
    std::string input;
    unsigned number;
    bool done = false;

    do {
        input = getInput(prompt);

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

bool UserInterface::inRange(long n, long min, long max) {
    bool b = (n <= max) && (n >= min);

    if (!b)
        _errorMessage = "Value outside allowed range!\n";

    return b;
}

Client *UserInterface::getOrCreateClient(Company &comp, unsigned nif) {
    for (Client *c : comp.getClients())
        if (c->getNIF() == nif)
            return c;

    std::cout << "\nIt seems you have never travelled with us... :(\n";
    std::string name =
        getInput("To finish your registration insert your name: ");

    return comp.createClient(nif, name);
}

void UserInterface::mainMenu() {
    optionsMenu(COMPANY_NAME,
                {{"Exit", EXIT}, {"Client", C_AUTH}, {"Employee", E_AUTH}});
}

void UserInterface::clientAuthMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Client login\n"
              << std::endl;

    unsigned nif = getNumberInput("Please enter your NIF: ");

    _currentClient = getOrCreateClient(comp, nif);
    _currentMenu = C_OPTIONS;
}
void UserInterface::clientOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Welcome " + _currentClient->getName() + "!",
                {{"Go back", MAIN},
                 {"Check my flights", C_CHECK_FLIGHTS},
                 {"Buy tickets", C_BUY_TICKETS},
                 {"See transports", C_CHECK_TRANSPORTS}});
}
void UserInterface::cCheckFlightsMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Your flights\n\n";
    printTickets(_currentClient->getTickets());
    getInput("\nPress Enter to continue\n");
    _currentMenu = C_OPTIONS;
}
void UserInterface::cBuyTicketsMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Available flights\n\n";

    printFlights(comp.getFlights());

    Flight *flight;
    do {
        unsigned f = getNumberInput("\nChoose a flight (0 to go back): ");

        if (f == 0) {
            _currentMenu = C_OPTIONS;
            return;
        }

        flight = comp.findFlight(f);

        if (!flight)
            _errorMessage = "Invalid input!\n";
    } while (!flight);

    unsigned availability = flight->getAvailability();

    if (availability == 0) {
        std::cout
            << "\nIt seems there are no available tickets for this flight!\n";
        getInput("Press Enter to continue\n");
        _currentMenu = C_OPTIONS;
        return;
    }

    unsigned seats =
        getNumberInput("How many tickets would you like? ", 0, availability);

    for (unsigned i{1}; i <= seats; ++i) {
        std::cout << CLEAR_SCREEN << "Ticket " << i << " out of " << seats
                  << "\n\n";
        printPlaneLayout(flight);

        Ticket *ticket;
        while (true) {
            std::cout << std::endl;
            std::string seat = getInput("Pick a seat: ");

            if (!(ticket = flight->findTicketBySeat(seat)) ||
                ticket->getClient())
                _errorMessage = "That seat is unavailable!\n";
            else
                break;
        };

        unsigned nif = getNumberInput("Insert the passenger's NIF: ");
        Client *client = getOrCreateClient(comp, nif);

        ticket->setClient(client);
        client->addTicket(ticket);

        std::string autoLuggage =
            getInput("Do you wish to use automatic luggaging? (y/N) ");

        if (autoLuggage == "Y" || autoLuggage == "y") {
            Luggage *luggage = new Luggage(ticket);
            flight->getCart()->addLuggage(luggage);

            ticket->addLuggage(luggage);
        }

        std::cout << "\nThe ticket has been purchased!\n"
                     "Thanks for travelling with us... :D\n";

        getInput("Press Enter to continue\n");
    }

    _currentMenu = C_OPTIONS;
}
void UserInterface::cCheckTransportsMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Available transports\n\n";

    printAirports(comp.getAirports());
    std::cout << '\n';

    unsigned airportID =
        getNumberInput("Insert airport ID: ", 0, comp.getAirports().size() - 1);
    Airport *airport = comp.getAirports().at(airportID);

    std::cout << '\n';
    printTransports(airport->getTransports());

    getInput("\nPress Enter to continue\n");
    _currentMenu = C_OPTIONS;
}

void UserInterface::employeeAuthMenu() {
    std::cout << CLEAR_SCREEN << COMPANY_NAME
              << " - Employee login\n\n"
                 "Please enter your credentials"
              << std::endl;

    std::string username = getInput("Username: ");

    std::string password =
        getInput("Password: " + CONCEAL_TEXT + DISABLE_CURSOR);
    std::cout << ENABLE_CURSOR << RESET_FORMATTING;

    if (username == "admin" && password == "admin") {
        _currentMenu = E_OPTIONS;
    } else {
        _currentMenu = MAIN;
    }
}
void UserInterface::employeeOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - ADMIN", {{"Log off", MAIN},
                                            {"Planes", E_PLANE_OPTIONS},
                                            {"Flights", E_FLIGHT_OPTIONS},
                                            {"Services", E_SERVICE_OPTIONS},
                                            {"Airports", E_AIRPORT_OPTIONS},
                                            {"Transports", E_TRANSPORT_OPTIONS},
                                            {"Carts", E_CART_OPTIONS},
                                            {"Clients", E_CLIENT_OPTIONS}});
}

void UserInterface::ePlaneOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Planes", {{"Go back", E_OPTIONS},
                                             {"New plane", E_PLANE_CREATE},
                                             {"Plane info", E_PLANE_READ},
                                             {"Update plane", E_PLANE_UPDATE},
                                             {"Delete plane", E_PLANE_DELETE}});
}
void UserInterface::ePlaneCreateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - New plane\n\n";

    std::string plate = getInput("Insert the plane's plate: ");

    std::string type = getInput("Insert the plane's type: ");

    unsigned rows =
        getNumberInput("Insert the plane's rows (max. 26): ", 1, 26);

    unsigned cols = getNumberInput("Insert the plane's columns: ", 1);

    comp.createPlane(rows, cols, plate, type);

    std::cout << "\nPlane created!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_PLANE_OPTIONS;
}
void UserInterface::ePlaneReadMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME
              << " - Plane info\n\n"

                 "ID:       (1) Descending	(q) Ascending\n"
                 "Type:     (2) Descending	(w) Ascending\n"
                 "Plate:    (3) Descending	(e) Ascending\n"
                 "Capacity: (4) Descending	(r) Ascending\n"
                 "          (0) Go back\n\n";

    std::string opt = getInput("Choose an ordering strategy: ");

    std::vector<Plane *> sortedVec = comp.getPlanes();

    if (opt == "1") {
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getID() > p2->getID();
        });
    } else if (opt == "q") {
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getID() < p2->getID();
        });
    } else if (opt == "2") {
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getType() > p2->getType();
        });
    } else if (opt == "w") {
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getType() < p2->getType();
        });
    } else if (opt == "3") {
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getPlate() > p2->getPlate();
        });
    } else if (opt == "e") {
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getPlate() < p2->getPlate();
        });
    } else if (opt == "4") {
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getCapacity() > p2->getCapacity();
        });
    } else if (opt == "r") {
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane *p1, Plane *p2) {
            return p1->getCapacity() < p2->getCapacity();
        });
    } else if (opt == "0") {
        _currentMenu = E_PLANE_OPTIONS;
        return;
    } else {
        _errorMessage = "Invalid input!\n";
        return;
    }

    std::cout << '\n';
    printPlanes(sortedVec);

    getInput("\nPress Enter to continue\n");
}
void UserInterface::ePlaneUpdateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Update plane\n\n";

    unsigned id =
        getNumberInput("Insert the ID of the plane you wish to update: ", 0,
                       comp.getPlanes().size() - 1);
    Plane *plane = comp.getPlanes().at(id);

    std::cout << "Current rows: " << plane->getRows() << '\n';
    unsigned newRows =
        getNumberInput("New rows (0 to keep current value): ", 0, 26);

    std::cout << "Current columns: " << plane->getColumns() << '\n';
    unsigned newCols =
        getNumberInput("New columns (0 to keep current value): ", 0, 99);

    comp.updatePlane(plane, newRows, newCols);

    std::cout << "\nThe changes have been saved!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_PLANE_OPTIONS;
}
void UserInterface::ePlaneDeleteMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Delete plane\n\n";

    unsigned id =
        getNumberInput("Insert the ID of the plane you wish to delete: ", 0,
                       comp.getPlanes().size() - 1);
    Plane *plane = comp.getPlanes().at(id);

    std::string confirm = getInput("Confirm (y/N): ");
    if (confirm == "Y" || confirm == "y") {
        comp.deletePlane(plane);
        std::cout << "\nPlane deleted!\n";
    } else {
        std::cout << "\nPlane not deleted!\n";
    }

    getInput("Press Enter to continue\n");
    _currentMenu = E_PLANE_OPTIONS;
}

void UserInterface::eFlightOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Flights",
                {{"Go back", E_OPTIONS},
                 {"New flight", E_FLIGHT_CREATE},
                 {"Flight info", E_FLIGHT_READ},
                 {"Update flight", E_FLIGHT_UPDATE},
                 {"Delete flight", E_FLIGHT_DELETE}});
}
void UserInterface::eFlightCreateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - New flight\n\n";

    Airport *o;
    Airport *d;

    unsigned number = getNumberInput("Insert the flight number: ");

    unsigned duration = getNumberInput("Insert the flight duration: ");

    std::string origin = getInput("Insert the flight origin: ");

    std::string dest = getInput("Insert the flight destination: ");

    std::string departureDate = getInput("Insert the flight departure date: ");

    unsigned planeID = getNumberInput("Insert the flight's plane ID: ", 0,
                                      comp.getPlanes().size() - 1);
    Plane *plane = comp.getPlanes().at(planeID);

    if (!(o = comp.findAirport(origin)))
        o = comp.createAirport(origin);

    if (!(d = comp.findAirport(dest)))
        d = comp.createAirport(dest);

    comp.createFlight(number, duration, o, d, departureDate, plane);

    std::cout << "\nFlight created!\n" << std::endl;
    getInput("Press Enter to continue\n");
    _currentMenu = E_FLIGHT_OPTIONS;
}
void UserInterface::eFlightReadMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME
              << " - Flight info\n\n"
                 "Flight Number: (1) Descending	(q) Ascending\n"
                 "Duration:      (2) Descending	(w) Ascending\n"
                 "Plane ID:      (3) Descending	(e) Ascending\n"
                 "               (0) Go back\n\n";

    std::string opt = getInput("Choose an ordering strategy: ");

    std::vector<Flight *> sortedVec = comp.getFlights();

    if (opt == "1") {
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Flight *p1, Flight *p2) { return p1->getID() > p2->getID(); });
    } else if (opt == "q") {
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Flight *p1, Flight *p2) { return p1->getID() < p2->getID(); });
    } else if (opt == "2") {
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Flight *p1, Flight *p2) {
                      return p1->getDuration() > p2->getDuration();
                  });
    } else if (opt == "w") {
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Flight *p1, Flight *p2) {
                      return p1->getDuration() < p2->getDuration();
                  });
    } else if (opt == "3") {
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Flight *p1, Flight *p2) {
                      return p1->getPlane()->getID() > p2->getPlane()->getID();
                  });
    } else if (opt == "e") {
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Flight *p1, Flight *p2) {
                      return p1->getPlane()->getID() < p2->getPlane()->getID();
                  });
    } else if (opt == "0") {
        _currentMenu = E_FLIGHT_OPTIONS;
        return;
    } else {
        _errorMessage = "Invalid input!\n";
        return;
    }

    printFlights(sortedVec);
    getInput("\nPress Enter to continue\n");
}
void UserInterface::eFlightUpdateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Update flight\n\n";

    unsigned id =
        getNumberInput("Insert the ID of the plane you wish to update: ", 0,
                       comp.getFlights().size() - 1);
    Flight *flight = comp.getFlights().at(id);

    std::cout << "Current duration: " << flight->getDuration() << std::endl;
    unsigned newDuration =
        getNumberInput("New duration (0 to keep current value): ");

    std::cout << "Current origin: " << flight->getOrigin()->getName()
              << std::endl;
    std::string newOrigin =
        getInput("New origin (press Enter to keep current value): ");

    std::cout << "Current destination: " << flight->getDestination()->getName()
              << std::endl;
    std::string newDest =
        getInput("New destination (press Enter to keep current value): ");

    std::cout << "Current departure date: " << flight->getDepartureDate()
              << std::endl;
    std::string newDeparture =
        getInput("New departure date (press Enter to keep current value): ");

    std::cout << "Current plane ID: " << flight->getPlane()->getID()
              << std::endl;
    unsigned newPlaneID =
        getNumberInput("New plane ID (press Enter to keep current value): ", 0,
                       comp.getPlanes().size() - 1);

    comp.updateFlight(flight, newDuration, newOrigin, newDest, newDeparture,
                      newPlaneID);

    std::cout << "\nThe changes have been saved!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_FLIGHT_OPTIONS;
}
void UserInterface::eFlightDeleteMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Delete flight\n\n";

    unsigned id =
        getNumberInput("Insert the ID of the flight you wish to delete: ", 0,
                       comp.getFlights().size() - 1);
    Flight *flight = comp.getFlights().at(id);

    std::string confirm = getInput("Confirm (y/N): ");
    if (confirm == "Y" || confirm == "y") {
        comp.deleteFlight(flight);
        std::cout << "\nFlight deleted!\n";
    } else {
        std::cout << "\nFlight not deleted!\n";
    }

    getInput("Press Enter to continue\n");
    _currentMenu = E_FLIGHT_OPTIONS;
}

void UserInterface::eServiceOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Services",
                {{"Go back", E_OPTIONS},
                 {"New service", E_SERVICE_CREATE},
                 {"Service info", E_SERVICE_READ},
                 {"Do service", E_SERVICE_COMPLETE}});
}
void UserInterface::eServiceCreateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - New service\n\n";

    unsigned t = getNumberInput(
        "(0) Cleaning\n(1) Maintenance\n\nInsert the service's type: ", 0, 1);
    ServiceType type = static_cast<ServiceType>(t);

    std::string worker = getInput("Insert the service's responsible worker: ");

    std::string date = getInput("Insert the service's date (DD/MM/YY): ");

    unsigned planeID = getNumberInput(
        "Insert the id of the plane that will receive this service: ", 0,
        comp.getPlanes().size() - 1);
    Plane *plane = comp.getPlanes().at(planeID);

    Service service = Service(type, date, worker);
    plane->addService(service);

    std::cout << "\nService created!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_SERVICE_OPTIONS;
}
void UserInterface::eServiceReadMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Service info\n\n";

    printServices(comp.getPlanes());
    getInput("\nPress Enter to continue\n");
    _currentMenu = E_SERVICE_OPTIONS;
}
void UserInterface::eServiceCompleteMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Do service\n\n";

    printPlanes(comp.getPlanes());

    unsigned planeID = getNumberInput("Insert the ID of the plane: ", 0,
                                      comp.getPlanes().size() - 1);

    comp.getPlanes().at(planeID)->doService();

    std::cout << "\nService done...\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_SERVICE_OPTIONS;
}

void UserInterface::eClientOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Clients",
                {{"Go back", E_OPTIONS},
                 {"New client", E_CLIENT_CREATE},
                 {"Client info", E_CLIENT_READ},
                 {"Update client", E_CLIENT_UPDATE},
                 {"Delete client", E_CLIENT_DELETE}});
}
void UserInterface::eClientCreateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - New client\n\n";

    unsigned nif = getNumberInput("Insert the client's NIF: ");

    if (comp.findClient(nif)) {
        "\nThat client already exists!\n";
        getInput("Press Enter to continue\n");
        _currentMenu = E_CLIENT_OPTIONS;
        return;
    }

    std::string name = getInput("Insert the client's name: ");

    comp.createClient(nif, name);

    std::cout << "\nClient created!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_CLIENT_OPTIONS;
}
void UserInterface::eClientReadMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME
              << " - Client info\n\n"

                 "NIF:  (1) Descending	(q) Ascending\n"
                 "Name: (2) Descending	(w) Ascending\n"
                 "      (0) Go back\n\n";

    std::string opt = getInput("Choose an ordering strategy: ");

    std::vector<Client *> sortedVec = comp.getClients();

    if (opt == "1") {
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Client *c1, Client *c2) { return c1->getNIF() > c2->getNIF(); });
    } else if (opt == "q") {
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Client *c1, Client *c2) { return c1->getNIF() < c2->getNIF(); });
    } else if (opt == "2") {
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Client *c1, Client *c2) {
                      return c1->getName() > c2->getName();
                  });
    } else if (opt == "w") {
        std::vector<Client *> sortedVec = comp.getClients();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Client *c1, Client *c2) {
                      return c1->getName() < c2->getName();
                  });
    } else if (opt == "0") {
        _currentMenu = E_CLIENT_OPTIONS;
        return;
    } else {
        _errorMessage = "Invalid input!\n";
        return;
    }

    std::cout << '\n';
    printClients(sortedVec);

    getInput("\nPress Enter to continue\n");
}
void UserInterface::eClientUpdateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Update client\n\n";

    Client *client;

    while (true) {
        unsigned nif =
            getNumberInput("Insert the NIF of the client you wish to update: ");

        if (client = comp.findClient(nif))
            break;
        else
            _errorMessage = "That client does not exist!\n";
    }

    std::cout << "Current name: " << client->getName() << std::endl;
    std::string newName =
        getInput("New name (press Enter to keep current value): ");

    comp.updateClient(client, newName);

    std::cout << "\nThe changes have been saved!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_CLIENT_OPTIONS;
}
void UserInterface::eClientDeleteMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Delete client\n\n";

    Client *client;

    while (true) {
        unsigned nif =
            getNumberInput("Insert the NIF of the client you wish to delete: ");

        if (client = comp.findClient(nif))
            break;
        else
            _errorMessage = "That client does not exist!\n";
    }

    std::string confirm = getInput("Confirm (y/N): ");
    if (confirm == "Y" || confirm == "y") {
        comp.deleteClient(client);
        std::cout << "\nClient deleted!\n";
    } else {
        std::cout << "\nClient not deleted!\n";
    }

    getInput("Press Enter to continue\n");
    _currentMenu = E_CLIENT_OPTIONS;
}

void UserInterface::eAirportOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Airports",
                {{"Go back", E_OPTIONS},
                 {"New airport", E_AIRPORT_CREATE},
                 {"Airport info", E_AIRPORT_READ},
                 {"Delete airport", E_AIRPORT_DELETE}});
}
void UserInterface::eAirportCreateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - New airport\n\n";

    std::string name;

    do {
        name = getInput("Insert the name of the airport: ");
        _errorMessage = "That airport already exists!";
    } while (comp.findAirport(name));
    _errorMessage = "";

    comp.createAirport(name);

    std::cout << "\nAirport created!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_AIRPORT_OPTIONS;
}
void UserInterface::eAirportReadMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Airport info\n\n";

    printAirports(comp.getAirports());

    getInput("\nPress Enter to continue\n");
    _currentMenu = E_AIRPORT_OPTIONS;
}
void UserInterface::eAirportDeleteMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Delete airport\n\n";

    unsigned id =
        getNumberInput("Insert the ID of the airport you wish to delete: ", 0,
                       comp.getAirports().size() - 1);
    Airport *airport = comp.getAirports().at(id);

    std::string confirm = getInput("Confirm (y/N): ");
    if (confirm == "Y" || confirm == "y") {
        comp.deleteAirport(airport);
        std::cout << "\nAirport deleted!\n";
    } else {
        std::cout << "\nAirport not deleted!\n";
    }

    getInput("Press Enter to continue\n");
    _currentMenu = E_AIRPORT_OPTIONS;
}

void UserInterface::eCartOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Carts", {{"Go back", E_OPTIONS},
                                            {"Cart info", E_CART_READ},
                                            {"Update cart", E_CART_UPDATE}});
}
void UserInterface::eCartReadMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Cart info\n\n";

    printCarts(comp.getFlights());
    getInput("\nPress Enter to continue\n");
    _currentMenu = E_CART_OPTIONS;
}
void UserInterface::eCartUpdateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Update cart\n\n";

    unsigned id = getNumberInput(
        "Insert the ID of the flight whose cart you wish to update: ", 0,
        comp.getFlights().size() - 1);
    Cart *cart = comp.getFlights().at(id)->getCart();

    std::cout << "Current cart size: " << cart->getCartSize() << '\n';
    unsigned newCartSize =
        getNumberInput("New cart size (0 to keep current value): ", 0);

    std::cout << "Current trolley size: " << cart->getTrolleySize() << '\n';
    unsigned newTrolleySize =
        getNumberInput("New trolley size (0 to keep current value): ", 0);

    std::cout << "Current stack size: " << cart->getStackSize() << '\n';
    unsigned newStackSize =
        getNumberInput("New stack size (0 to keep current value): ", 0);

    cart->setSizes(newCartSize, newTrolleySize, newStackSize);

    std::cout << "\nThe changes have been saved!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_CART_OPTIONS;
}

void UserInterface::eTransportOptionsMenu() {
    optionsMenu(COMPANY_NAME + " - Transports",
                {{"Go back", E_OPTIONS},
                 {"New transport", E_TRANSPORT_CREATE},
                 {"Transport info", E_TRANSPORT_READ},
                 {"Update transport", E_TRANSPORT_UPDATE},
                 {"Delete transport", E_TRANSPORT_DELETE}});
}
void UserInterface::eTransportCreateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - New transport\n\n";

    unsigned t = getNumberInput(
        "(0) Train\n(1) Bus\n(2) Metro\nInsert the tranport's type: ", 0, 2);
    TransportType type = static_cast<TransportType>(t);

    std::string name = getInput("Insert the tranport's name: ");

    unsigned distance = getNumberInput(
        "Insert the transport's distance to the nearest airport: ");

    Transport transport{type, distance, name};

    while (true) {
        std::string time = getInput(
            "Insert a transport's schedule (hh:mm) [press Enter to end]: ");
        if (time == "") {
            break;
        }
        transport.insertTime(time);
    }

    std::cout << "ID - Name" << std::endl;
    for (auto a : comp.getAirports()) {
        std::cout << a->getID() << " - " << a->getName() << std::endl;
    }

    unsigned airportID =
        getNumberInput("Insert the ID of the nearest airport: ", 0);
    Airport *airport = comp.getAirports().at(airportID);

    airport->addTransport(transport);

    std::cout << "\nTransport created!\n";
    getInput("Press Enter to continue\n");
    _currentMenu = E_TRANSPORT_OPTIONS;
}
void UserInterface::eTransportReadMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Transport info\n\n";

    unsigned airportID =
        getNumberInput("Insert the ID of the airport for which you want to see "
                       "the transports: ",
                       0, comp.getAirports().size());
    Airport *airport = comp.getAirports().at(airportID);

    unsigned reverse =
        getNumberInput("\n(0) Ascending distance\n(1) Descending distance\n"
                       "Choose ordering strategy: ",
                       0, 1);
    std::cout << '\n';

    printTransports(airport->getTransports(), reverse);

    getInput("\nPress Enter to continue\n");
    _currentMenu = E_TRANSPORT_OPTIONS;
}
void UserInterface::eTransportUpdateMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Update transport\n\n";

    unsigned cnt{0};
    for (auto a : comp.getAirports()) {
        auto &transports{a->getTransports()};
        for (auto t{transports.begin()}, end{transports.end()}; t != end; ++t) {
            std::cout << cnt++ << " - " << t->getElement().getName()
                      << std::endl;
        }
    }

    std::cout << '\n' << std::flush;

    unsigned id = getNumberInput(
        "Insert the ID of the transport you wish to update: ", 0, cnt - 1);

    cnt = 0;
    Transport *transport = nullptr;
    for (auto a : comp.getAirports()) {
        auto &transports{a->getTransports()};
        for (auto t{transports.begin()}, end{transports.end()}; t != end; ++t) {
            if (cnt++ == id) {
                transport = &t->getElement();
                break;
            }
        }
    }

    std::cout << "Current transport name: " << transport->getName() << '\n';
    std::string name =
        getInput("New transport name (press Enter to keep current value): ");

    if (name != "")
        transport->setName(name);

    auto &timetable{transport->getTimetable()};
    for (auto i{timetable.begin()}, end{timetable.end()}; i != end; ++i)
        std::cout << i->getElement() << std::endl;

    while (true) {
        std::string hour = getInput(
            "Insert a transport's schedule (hh/mm) [press Enter to end]: ");
        if (hour == "")
            break;
        transport->insertTime(hour);
    }

    std::cout << "Transport updated!\n" << std::flush;
    getInput("Press Enter to continue\n");
    _currentMenu = E_TRANSPORT_OPTIONS;
}
void UserInterface::eTransportDeleteMenu(Company &comp) {
    std::cout << CLEAR_SCREEN << COMPANY_NAME << " - Delete transport\n\n";

    unsigned cnt{0};
    for (auto a : comp.getAirports()) {
        auto &transports{a->getTransports()};
        for (auto t{transports.begin()}, end{transports.end()}; t != end; ++t) {
            std::cout << cnt++ << " - " << t->getElement().getName()
                      << std::endl;
        }
    }

    std::cout << '\n' << std::flush;

    unsigned id = getNumberInput(
        "Insert the ID of the transport you wish to delete: ", 0, cnt - 1);

    std::string confirm = getInput("Confirm (y/N): ");
    if (confirm == "Y" || confirm == "y") {
        cnt = 0;
        std::string confirm;
        for (auto a : comp.getAirports()) {
            auto &transports{a->getTransports()};
            for (auto t{transports.begin()}, end{transports.end()}; t != end;
                 ++t) {
                if (id == cnt++) {
                    transports.remove(t->getElement());
                    break;
                }
            }
        }
        std::cout << "\nTransport deleted!\n";
    } else {
        std::cout << "\nTransport not deleted!\n";
    }

    getInput("Press Enter to continue\n");
    _currentMenu = E_TRANSPORT_OPTIONS;
}

void UserInterface::show(Company &comp) {
    switch (_currentMenu) {
    case MAIN:
        mainMenu();
        break;

    case C_AUTH:
        clientAuthMenu(comp);
        break;
    case C_OPTIONS:
        clientOptionsMenu();
        break;
    case C_CHECK_FLIGHTS:
        cCheckFlightsMenu(comp);
        break;
    case C_BUY_TICKETS:
        cBuyTicketsMenu(comp);
        break;
    case C_CHECK_TRANSPORTS:
        cCheckTransportsMenu(comp);
        break;

    case E_AUTH:
        employeeAuthMenu();
        break;
    case E_OPTIONS:
        employeeOptionsMenu();
        break;

    case E_PLANE_OPTIONS:
        ePlaneOptionsMenu();
        break;
    case E_PLANE_CREATE:
        ePlaneCreateMenu(comp);
        break;
    case E_PLANE_READ:
        ePlaneReadMenu(comp);
        break;
    case E_PLANE_UPDATE:
        ePlaneUpdateMenu(comp);
        break;
    case E_PLANE_DELETE:
        ePlaneDeleteMenu(comp);
        break;

    case E_FLIGHT_OPTIONS:
        eFlightOptionsMenu();
        break;
    case E_FLIGHT_CREATE:
        eFlightCreateMenu(comp);
        break;
    case E_FLIGHT_READ:
        eFlightReadMenu(comp);
        break;
    case E_FLIGHT_UPDATE:
        eFlightUpdateMenu(comp);
        break;
    case E_FLIGHT_DELETE:
        eFlightDeleteMenu(comp);
        break;

    case E_SERVICE_OPTIONS:
        eServiceOptionsMenu();
        break;
    case E_SERVICE_CREATE:
        eServiceCreateMenu(comp);
        break;
    case E_SERVICE_READ:
        eServiceReadMenu(comp);
        break;
    case E_SERVICE_COMPLETE:
        eServiceCompleteMenu(comp);
        break;

    case E_CLIENT_OPTIONS:
        eClientOptionsMenu();
        break;
    case E_CLIENT_CREATE:
        eClientCreateMenu(comp);
        break;
    case E_CLIENT_READ:
        eClientReadMenu(comp);
        break;
    case E_CLIENT_UPDATE:
        eClientUpdateMenu(comp);
        break;
    case E_CLIENT_DELETE:
        eClientDeleteMenu(comp);
        break;

    case E_AIRPORT_OPTIONS:
        eAirportOptionsMenu();
        break;
    case E_AIRPORT_CREATE:
        eAirportCreateMenu(comp);
        break;
    case E_AIRPORT_READ:
        eAirportReadMenu(comp);
        break;
    case E_AIRPORT_DELETE:
        eAirportDeleteMenu(comp);
        break;

    case E_CART_OPTIONS:
        eCartOptionsMenu();
        break;
    case E_CART_READ:
        eCartReadMenu(comp);
        break;
    case E_CART_UPDATE:
        eCartUpdateMenu(comp);
        break;

    case E_TRANSPORT_OPTIONS:
        eTransportOptionsMenu();
        break;
    case E_TRANSPORT_CREATE:
        eTransportCreateMenu(comp);
        break;
    case E_TRANSPORT_READ:
        eTransportReadMenu(comp);
        break;
    case E_TRANSPORT_UPDATE:
        eTransportUpdateMenu(comp);
        break;
    case E_TRANSPORT_DELETE:
        eTransportDeleteMenu(comp);
        break;

    default:
        throw Exit();
        break;
    }
}

void UserInterface::exit() {
    std::cout << CLEAR_SCREEN << std::flush;
    loadString("Shutting down...", 1000);
}
