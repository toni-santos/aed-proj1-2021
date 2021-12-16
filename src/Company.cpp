#include "../includes/Company.h"
#include "../includes/Exceptions.h"
#include "../includes/Plane.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"

void Company::populate() {
    readAirport();
    readPlane();
    readClient();
}

// DONE
Client *Company::createClient(unsigned nif, std::string name) {
    Client *client = new Client(_clients.size(), nif, name);
    _clients.push_back(client);
    return client;
}

// DONE
void Company::updateClient(Client *client, std::string name) {
    if (name != "")
        client->setName(name);
}

// DONE
void Company::deleteClient(Client *client) {
    _clients.at(client->getID()) = nullptr;

    delete client;
}

// DONE
Flight *Company::createFlight(unsigned number, unsigned duration,
                              Airport *origin, Airport *dest,
                              std::string departure, Plane *plane) {
    Flight *flight = new Flight(_flights.size(), number, duration, origin, dest,
                                departure, plane);
    _flights.push_back(flight);
    return flight;
}

// DONE
void Company::updateFlight(Flight *flight, std::string duration,
                           std::string origin, std::string dest,
                           std::string departure, std::string plane) {
    if (duration != "")
        flight->setDuration(stoul(duration));

    if (origin != "")
        flight->setOrigin(_airports.at(stoul(origin)));

    if (dest != "")
        flight->setDestination(_airports.at(stoul(dest)));

    if (departure != "")
        flight->setDepartureDate(departure);

    if (plane != "")
        flight->setPlane(_planes.at(stoul(plane)));
}

// DONE
void Company::deleteFlight(Flight *flight) {
    _flights.at(flight->getID()) = nullptr;

    delete flight;
}

// DONE
Plane *Company::createPlane(unsigned rows, unsigned columns, std::string plate,
                            std::string type) {
    Plane *plane = new Plane(_planes.size(), rows, columns, plate, type);
    _planes.push_back(plane);
    return plane;
}

// DONE
void Company::updatePlane(Plane *plane, std::string rows, std::string columns) {
    if (rows != "")
        plane->setRows(stoul(rows));

    if (columns != "")
        plane->setColumns(stoul(rows));
}

// DONE
void Company::deletePlane(Plane *plane) {
    _planes.at(plane->getID()) = nullptr;

    auto flights = plane->getFlights();
    while (!flights.empty()) {
        deleteFlight(flights.front());
        flights.pop();
    }

    delete plane;
}

// DONE
Airport *Company::createAirport(std::string name) {
    Airport *airport = new Airport(_airports.size(), name);
    _airports.push_back(airport);
    return airport;
}

// DONE
void Company::updateAirport(Airport *airport, std::string name) {
    if (name != "")
        airport->setName(name);
}

// DONE
void Company::deleteAirport(Airport *airport) {
    _airports.at(airport->getID()) = nullptr;

    delete airport;
}

Plane *Company::findPlane(unsigned id) {
    for (Plane *p : _planes) {
        if (p->getID() == id) {
            return p;
        }
    }

    return nullptr;
}

Airport *Company::findAirport(std::string name) {
    for (Airport *a : _airports) {
        if (a->getName() == name) {
            return a;
        }
    }
    return nullptr;
}

Flight *Company::findFlight(unsigned number) {
    for (Flight *f : _flights) {
        if (f->getNumber() == number) {
            return f;
        }
    }

    return nullptr;
}

Client *Company::findClient(unsigned nif) {
    for (Client *c : _clients) {
        if (c->getNIF() == nif) {
            return c;
        }
    }
    return nullptr;
}

std::vector<std::pair<int, int>> parseClientTickets(std::string vec) {
    std::vector<std::pair<int, int>> result;

    if (vec.empty())
        return result;

    std::vector<std::string> parsedTickets = split(vec, ';');
    for (auto t : parsedTickets) {
        std::vector<std::string> ids = split(t, ',');
        result.push_back({stoul(ids.at(0)), stoul(ids.at(1))});
    }

    return result;
}

void Company::readAirport() {
    std::ifstream f{AIRPORT_FILE_PATH};

    if (f.fail())
        throw ReadError();

    while (!f.eof()) {
        std::string line;
        // std::vector<std::string> parsedLine;
        getline(f, line);
        // parsedLine = split(line, '\t');

        createAirport(line);
    }
    f.close();
}

void Company::readPlane() {
    std::ifstream f{PLANE_FILE_PATH};

    if (f.fail())
        throw ReadError();

    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);
        parsedLine = split(line, '\t');

        unsigned rows = stoul(parsedLine.at(0));
        unsigned columns = stoul(parsedLine.at(1));
        std::string plate = parsedLine.at(2);
        std::string type = parsedLine.at(3);

        Plane *plane = createPlane(rows, columns, plate, type);

        // READ FLIGHTS
        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');

            unsigned number = stoul(parsedLine.at(0));
            unsigned duration = stoul(parsedLine.at(1));
            unsigned originIndex = stoul(parsedLine.at(2));
            unsigned destIndex = stoul(parsedLine.at(3));
            std::string date = parsedLine.at(4);

            Flight *flight =
                createFlight(number, duration, _airports.at(originIndex),
                             _airports.at(destIndex), date, plane);
        }

        // READ DONE SERVICES
        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');

            unsigned type = stoul(parsedLine.at(0));
            std::string date = parsedLine.at(1);
            std::string worker = parsedLine.at(2);

            plane->addService({type, date, worker});
            plane->doService();
        }

        // READ SERVICES
        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');

            unsigned type = stoul(parsedLine.at(0));
            std::string date = parsedLine.at(1);
            std::string worker = parsedLine.at(2);

            plane->addService({type, date, worker});
        }
    }
    f.close();
}

void Company::readClient() {
    std::ifstream f{CLIENT_FILE_PATH};

    if (f.fail())
        throw ReadError();

    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        std::getline(f, line);
        parsedLine = split(line, '\t');

        unsigned nif = stoul(parsedLine.at(0));
        std::string name = parsedLine.at(1);

        Client *client = createClient(nif, name);

        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');

            unsigned flightID = stoul(parsedLine.at(0));
            std::string seat = parsedLine.at(1);

            client->addTicket(_flights.at(flightID)->findTicketBySeat(seat));
        }
    }

    f.close();
}

void Company::writeAirport() {
    std::ofstream of{AIRPORT_FILE_PATH};

    if (of.fail())
        throw ReadError();

    for (Airport *airport : _airports) {
        of << airport->getName() << '\n';
    }
}

// DONE
void Company::writePlane() {
    std::ofstream of{PLANE_FILE_PATH};

    if (of.fail())
        throw ReadError();

    for (Plane *plane : _planes) {
        of << plane->getRows() << '\t' << plane->getColumns() << '\t'
           << plane->getPlate() << '\t' << plane->getType() << '\n';

        auto flights = plane->getFlights();
        while (!flights.empty()) {
            Flight *flight = flights.front();
            flights.pop();
            of << flight->getNumber() << '\t' << flight->getDuration() << '\t'
               << flight->getOrigin()->getID() << '\t'
               << flight->getDestination()->getID() << '\t'
               << flight->getDepartureDate() << '\n';
        }

        auto servicesDone = plane->getServicesDone();
        while (!servicesDone.empty()) {
            Service service = servicesDone.front();
            servicesDone.pop();
            of << service.getType() << service.getDate() << service.getWorker()
               << '\n';
        }

        auto services = plane->getServices();
        while (!services.empty()) {
            Service service = services.front();
            servicesDone.pop();
            of << service.getType() << service.getDate() << service.getWorker()
               << '\n';
        }

        of << '\n';
    }
}

// DONE
void Company::writeClient() {
    std::ofstream of{CLIENT_FILE_PATH};

    if (of.fail())
        throw ReadError();

    for (Client *c : _clients) {
        of << c->getNIF() << '\t' << c->getName() << '\n';

        bool first{true};
        for (Ticket *t : c->getTickets())
            of << t->getFlight()->getID() << '\t' << t->getSeat();

        of << '\n';
    }
}
