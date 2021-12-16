#include "../includes/UserInterface.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

// TODO: WRITE/DELETE FROM FILES
// TODO: DESTINATIONS
// TODO: LUGGAGE
// TODO: BST DAS DESTINATIONS


void printServiceQueue(Plane* plane) {
	std::queue<Service> tqueue = plane->getServices();
	std::cout << "Type - Date - Worker" << std::endl;
	while (tqueue.size() != 0) {
		Service s = tqueue.front();
		tqueue.pop();
		std::cout << s.getType() << " - "  << s.getDate() << " - " << s.getWorker() << std::endl;
	}
}


void printPlaneVector(std::vector<Plane*> sortedVec) {
    std::cout << "ID - Type - Plate - Capacity - Flights\n\n" << std::flush;
    for (const Plane *plane : sortedVec) {
        std::string fls;
        std::queue<Flight *> tempq = plane->getFlights();
        while (tempq.size() != 0) {
            fls += " " + (tempq.front()->getID());
            tempq.pop();
        }

        std::cout << plane->getID() << " - " << plane->getType() << " - "
                  << plane->getPlate() << " - " << plane->getCapacity() << " -"
                  << fls << std::endl;
    }
}

void printClientFlights(Client *client, Company &comp) {
    for (auto ticket : client->getTickets()) {
        Flight *f = comp.findFlight(ticket->getFlight()->getID());

        std::cout << "Ticket: " << ticket->getFlight()->getID() << '\n'
                  << "Flight Number:" << f->getNumber() << '\n'
                  << "From->To:" << f->getOrigin() << "->"
                  << f->getDestination() << '\n'
                  << "Date of Departure: " << f->getDepartureDate() << '\n'
                  << "---------------------" << std::endl;
    }
}

void printClientVector(std::vector<Client*> sortedVec, Company &comp) {
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
    for (Client *c : comp.getClients()) {
        if (c->getNIF() == stoul(userNIF)) {
            currClient = c;
            loadString("Connecting you to our services...", 3000);
            _currentMenu = CLIENT_OPTIONS;
        }
    }

    std::cout << "It seems you have never travelled with us... :(\n"
              << "To finish your registration insert your name: " << std::flush;

    getInput(name);

    if (isDigitOnly(userNIF)) {
        currClient = comp.createClient(stoul(userNIF), name);
        std::cout << "Thanks for choosing " << STRIKE_THROUGH << "[REDACTED]"
                  << RESET_FORMATTING << " Airlines!" << std::endl;
        _currentMenu = CLIENT_OPTIONS;
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
    for (const Plane* plane : comp.getPlanes()) {
        text << plane->getID() << '\n';
    }

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New service", CREATE_SERVICE},
                             {"Check services", READ_SERVICE}});
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

void UserInterface::createPlane(Company &comp) {
    std::string plate, type, strRow, strCol, strId;
    unsigned id;
    bool flag = true;

    std::cout << "Insert the plane's plate: " << std::flush;
    getInput(plate);

    std::cout << "Insert the plane's type: " << std::flush;
    getInput(type);

    std::cout << "Insert the plane's row (max. 26): " << std::flush;
    getInput(strRow);

	std::cout << "Insert the plane's column: " << std::flush;
	getInput(strCol);

    std::cout << "Insert the plane's ID: " << std::flush;
    getInput(strId);

    for (auto p : comp.getPlanes()) {
        if (stoul(strId) == p->getID()) {
            std::cout
                << "A plane with that ID already exists! Re-enter the data..."
                << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            flag = false;
        }
    }
    if (flag) {
        if (isDigitOnly(strCol) && isDigitOnly(strRow) && isDigitOnly(strId)) {
            std::cout << "\nCreating the plane..." << std::flush;
			comp.createPlane(stoul(strRow), stoul(strCol), plate, type);
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
    std::string opt;
    std::cout << "Choose an ordering strategy..." << std::endl;

    std::cout << "ID: (1) Descending	(q) Ascending" << std::endl;
    std::cout << "Type: (2) Descending	(w) Ascending" << std::endl;
    std::cout << "Plate: (3) Descending	(e) Ascending" << std::endl;
    std::cout << "Capacity: (4) Descending	(r) Ascending" << std::endl;
    std::cout << "(0) Go back" << std::endl;
    getInput(opt);

    if (opt == "1") {
        std::vector<Plane*> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Plane* p1, Plane* p2) { return p1->getID() > p2->getID(); });

        printPlaneVector(sortedVec);

    } else if (opt == "q") {
        std::vector<Plane*> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(),
                  [](Plane* p1, Plane* p2) { return p1->getID() < p2->getID(); });

        printPlaneVector(sortedVec);

    } else if (opt == "2") {
        std::stringstream text;

        std::vector<Plane*> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane* p1, Plane* p2) {
            return p1->getType() > p2->getType();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "w") {
        std::stringstream text;

        std::vector<Plane*> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane* p1, Plane* p2) {
            return p1->getType() < p2->getType();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "3") {
        std::stringstream text;

        std::vector<Plane*> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane* p1, Plane* p2) {
            return p1->getPlate() > p2->getPlate();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "e") {
        std::stringstream text;

        std::vector<Plane*> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane* p1, Plane* p2) {
            return p1->getPlate() < p2->getPlate();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "4") {
        std::stringstream text;

        std::vector<Plane*> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane* p1, Plane* p2) {
            return p1->getCapacity() > p2->getCapacity();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "r") {
        std::stringstream text;

        std::vector<Plane*> sortedVec = comp.getPlanes();
        std::sort(sortedVec.begin(), sortedVec.end(), [](Plane* p1, Plane* p2) {
            return p1->getCapacity() < p2->getCapacity();
        });

        printPlaneVector(sortedVec);

    } else if (opt == "0") {
        std::cout << "Returning to the previous menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = PLANES;
    } else {
        std::cout << "That's not a valid input! Please choose a valid one..."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = READ_PLANE;
    }
}

void UserInterface::updatePlane(Company &comp) {
    std::string strId, newRows, newCols;
    bool flag = true;

    std::cout << "Insert the ID of the plane you wish to update: "
              << std::flush;
    getInput(strId);

    for (Plane* plane : comp.getPlanes()) {
        if (stoul(strId) == plane->getID()) {
			std::cout
					<< "Current capacity: " << plane->getRows()
					<< '\n'
					<< "New capacity (press Enter to not alter the current one): "
					<< std::flush;
			getInput(newRows);

			std::cout
					<< "Current capacity: " << plane->getColumns()
					<< '\n'
					<< "New capacity (press Enter to not alter the current one): "
					<< std::flush;
			getInput(newCols);

            comp.updatePlane(plane, newRows, newCols);

            std::cout << "The changes have been saved!\n"
                      << "Returning to the previous menu..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            flag = false;
        }
    }
    if (flag) {
        std::cout << "That client does not exist! Re-enter the NIF..."
                  << std::endl;
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
    for (Plane *plane: comp.getPlanes()) {
        if (stoul(strId) == plane->getID()) {
            do {
                std::cout << "Confirm (Y/N): " << std::flush;
                getInput(confirm);
                if (confirm == "Y") {
                    flag = false;
                    comp.deletePlane(plane);
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
            } while (flag);
            break;
        }
    }
    if (flag) {
        std::cout << "That plane does not exist! Re-enter the ID..."
                  << std::endl;
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
    for (Flight* flight : comp.getFlights()) {
        text << flight->getNumber() << " - " << flight->getDepartureDate()
             << " - " << flight->getOrigin() << "->" << flight->getDestination()
             << " - " << flight->getDuration() << '\n';
    }

    text << "\nChoose an operation...";

    optionsMenu(text.str(), {{"Go back", EMPLOYEE_OPTIONS},
                             {"New flight", CREATE_FLIGHT},
                             {"Check flight", READ_FLIGHT},
                             {"Update flight", UPDATE_FLIGHT},
                             {"Delete flight", DELETE_FLIGHT}});
}

void UserInterface::createFlight(Company &comp) {
	std::string strNumber, strDuration, origin, dest, departureDate, planeID;
	Airport* o;
	Airport* d;
	std::cout << "Insert the flight number: " << std::flush;
	getInput(strNumber);
	std::cout << "Insert the flight duration: " << std::flush;
	getInput(strDuration);
	std::cout << "Insert the flight origin: " << std::flush;
	getInput(origin);
	std::cout << "Insert the flight destination: " << std::flush;
	getInput(dest);
	std::cout << "Insert the flight departure date: " << std::flush;
	getInput(departureDate);
	std::cout << "Insert the flight plane's number: " << std::flush;
	getInput(planeID);

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

	if (comp.findPlane(stoul(planeID)) != nullptr) {
		std::cout << "That is not a valid plane! Please retry..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		_currentMenu = CREATE_FLIGHT;
	} else {
		comp.createFlight(stoul(strNumber), stoul(strDuration), o, d, departureDate, comp.findPlane(stoul(planeID)));
		std::cout << "Creating flight..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Done! Returning to previous menu!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		_currentMenu = FLIGHTS;
	}
}

void printFlightVector(std::vector<Flight *> sortedVec) {
	for (Flight* flight: sortedVec) {
		std::cout << flight->getNumber() << " - " << flight->getOrigin()->getName() << "->" << flight->getDestination()->getName() << " - " << flight->getDepartureDate() << " - " << flight->getDuration() << " - " << flight->getPlane()->getID() << std::endl;
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

	std::cout << "Flight Number - Origin->Destination - Departure Date - Duration - Plane ID" << std::flush;
	if (opt == "1") {
		std::vector<Flight*> sortedVec = comp.getFlights();
		std::sort(sortedVec.begin(), sortedVec.end(),
				  [](Flight* p1, Flight* p2) { return p1->getID() > p2->getID(); });

		printFlightVector(sortedVec);

	} else if (opt == "q") {
		std::vector<Flight*> sortedVec = comp.getFlights();
		std::sort(sortedVec.begin(), sortedVec.end(),
				  [](Flight* p1, Flight* p2) { return p1->getID() < p2->getID(); });

		printFlightVector(sortedVec);

	} else if (opt == "2") {
		std::vector<Flight*> sortedVec = comp.getFlights();
		std::sort(sortedVec.begin(), sortedVec.end(),
				  [](Flight* p1, Flight* p2) { return p1->getDuration() > p2->getDuration(); });

		printFlightVector(sortedVec);

	} else if (opt == "w") {
		std::vector<Flight*> sortedVec = comp.getFlights();
		std::sort(sortedVec.begin(), sortedVec.end(),
				  [](Flight* p1, Flight* p2) { return p1->getDuration() < p2->getDuration(); });

		printFlightVector(sortedVec);

	} else if (opt == "3") {
		std::vector<Flight*> sortedVec = comp.getFlights();
		std::sort(sortedVec.begin(), sortedVec.end(),
				  [](Flight* p1, Flight* p2) { return p1->getPlane()->getID() > p2->getPlane()->getID(); });

		printFlightVector(sortedVec);

	} else if (opt == "e") {
		std::vector<Flight*> sortedVec = comp.getFlights();
		std::sort(sortedVec.begin(), sortedVec.end(),
				  [](Flight* p1, Flight* p2) { return p1->getPlane()->getID() < p2->getPlane()->getID(); });

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
	std::string strId, newDuration, newOrigin, newDest, newDeparture, newPlaneID;
	bool flag = true;
	std::cout << "Insert the flight ID of the flight you wish to update: "
			  << std::flush;
	getInput(strId);
	for (Flight* flight: comp.getFlights()) {
		if (stoul(strId) == flight->getID()) {
			std::cout << "Current duration: " << flight->getDuration()
					  << '\n'
					  << "New duration (press Enter to not alter the current one): "
					  << std::flush;
			getInput(newDuration);

			std::cout << "Current origin: " << flight->getOrigin()
					  << '\n'
					  << "New origin (press Enter to not alter the current one): "
					  << std::flush;
			getInput(newOrigin);

			std::cout << "Current destination: " << flight->getDestination()
					  << '\n'
					  << "New destination (press Enter to not alter the current one): "
					  << std::flush;
			getInput(newDest);

			std::cout << "Current departure date: " << flight->getDepartureDate()
					  << '\n'
					  << "New departure date (press Enter to not alter the current one): "
					  << std::flush;
			getInput(newDeparture);

			std::cout << "Current plane ID: " << flight->getPlane()->getID()
					  << '\n'
					  << "New plane ID (press Enter to not alter the current one): "
					  << std::flush;
			getInput(newPlaneID);

			comp.updateFlight(flight, newDuration, newOrigin, newDest, newDeparture, newPlaneID);

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
	std::string strID, confirm;
	bool flag = true;
	std::cout << "Insert the flight ID of the flight you wish to delete: "
			  << std::flush;
	getInput(strID);
	for (Flight* flight: comp.getFlights()) {
		if (stoul(strID) == flight->getID()) {
			do {
				std::cout << "Confirm (Y/N): " << std::flush;
				getInput(confirm);
				if (confirm == "Y") {
					flag = false;
					comp.deleteFlight(flight);
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
			} while (flag);
			break;
		}
	}
	if (flag) {
		std::cout << "That flight does not exist! Re-enter the flight ID..."
				  << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		_currentMenu = DELETE_FLIGHT;
	} else {
		_currentMenu = FLIGHTS;
	}

}

void UserInterface::clientsMenu(Company &comp) {
    std::stringstream text;
    text << "These are all the clients:\n\n";

    for (const Client* client : comp.getClients()) {
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
    std::cout << "Insert the NIF of the client you wish to update: "
              << std::flush;
    getInput(strNIF);
    for (Client* client: comp.getClients()) {
        if (stoul(strNIF) == client->getNIF()) {
            std::cout << "Current name: " << client->getName()
                      << '\n'
                      << "New name (press Enter to not alter the current one): "
                      << std::flush;
            getInput(newName);

            comp.updateClient(client, newName);

            std::cout << "The changes have been saved!\n"
                      << "Returning to the previous menu..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            flag = false;
        }
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
    for (Client* client: comp.getClients()) {
        if (stoul(strNIF) == client->getNIF()) {
            do {
                std::cout << "Confirm (Y/N): " << std::flush;
                getInput(confirm);
                if (confirm == "Y") {
                    flag = false;
                    comp.deleteClient(client);
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
            } while (flag);
            break;
        }
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
    std::string name, strNIF;
    unsigned NIF;

    std::cout << "Insert the client's name: " << std::flush;

    getInput(name);

    std::cout << "Insert the client's NIF: " << std::flush;

    getInput(strNIF);

    if (isDigitOnly(strNIF)) {
        NIF = stoul(strNIF);
        std::cout << "\nCreating the client..." << std::flush;
        comp.createClient(stoul(strNIF), name);
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

void UserInterface::readClientMenu(Company &comp) {
    std::string opt;

    std::cout << "NIF: (1) Descending	(q) Ascending" << std::endl;
    std::cout << "Name: (2) Descending	(w) Ascending" << std::endl;
    std::cout << "(0) Go back..." << std::endl;
    getInput(opt);

    if (opt == "1") {
        std::vector<Client*> sortedVec = comp.getClients();
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Client* c1, Client* c2) { return c1->getNIF() > c2->getNIF(); });

        printClientVector(sortedVec, comp);

    } else if (opt == "q") {
        std::vector<Client*> sortedVec = comp.getClients();
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Client* c1, Client* c2) { return c1->getNIF() < c2->getNIF(); });

        printClientVector(sortedVec, comp);

    } else if (opt == "2") {
        std::vector<Client*> sortedVec = comp.getClients();
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Client* c1, Client* c2) { return c1->getName() > c2->getName(); });

        printClientVector(sortedVec, comp);

    } else if (opt == "w") {
        std::vector<Client*> sortedVec = comp.getClients();
        std::sort(
            sortedVec.begin(), sortedVec.end(),
            [](Client* c1, Client* c2) { return c1->getName() < c2->getName(); });

        printClientVector(sortedVec, comp);

    } else if (opt == "0") {
        std::cout << "Returning to the previous menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = SERVICES;
    } else {
        std::cout << "That's not a valid input! Please choose a valid one..."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _currentMenu = READ_SERVICE;
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
    std::string date, worker, planeid, type;
    std::cout << "Insert the service's type: " << std::flush;

    getInput(type);

    std::cout << "Insert the service's responsible worker: " << std::flush;

    getInput(worker);

    std::cout << "Insert the service's date (DD/MM/YY): " << std::flush;

    getInput(date);

    std::cout << "Insert the id of the plane that will receive this service: "
              << std::flush;

    getInput(planeid);

    Service service = Service(stoul(type), date, worker);
    for (Plane* plane: comp.getPlanes()) {
        if (stoul(planeid) == plane->getID()) {
            std::cout << "\nCreating the service..." << std::flush;
            plane->addService(service);
            break;
        } else {
            std::cout << "An error has occurred! Re-enter the data..."
                      << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            _currentMenu = CREATE_SERVICE;
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Created service: " << type << " - " << worker << std::endl;
    std::cout << "Returning to the previous menu..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    _currentMenu = SERVICES;
}

void UserInterface::readService(Company &comp) {
	for (Plane* plane: comp.getPlanes()) {
		std::cout << "Plane ID: " << plane->getID() << "\n\t"<< std::endl;
		printServiceQueue(plane);
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
