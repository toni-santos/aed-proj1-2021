#include "../includes/Company.h"
#include "../includes/Client.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
#include <iostream>

void Company::populate() {
    readPlane();
    readFlight();
    readService();
    readClient();
}

void Company::populateFlight(Plane plane, Flight flight) {
    plane.addFlight(flight.getNumber());
    for (int i = 0; i < plane.getCapacity(); i++) {
        flight.addTicket(Ticket(i, flight.getNumber()));
    }
}

Flight *Company::findFlight(unsigned flightID) {
    for (Flight &f : _flights) {
        if (f.getNumber() == flightID) {
            return &f;
        }
    }

    return nullptr;
}

Client *Company::findClient(unsigned NIF) {
    for (Client &c : _clients) {
        if (c.getNIF() == NIF) {
            // TODO: idk whats wrong
            return &c;
        }
    }
    return nullptr;
}

void Company::addClient(Client client) { _clients.push_back(client); }

void Company::addPlane(Plane plane) { _planes.push_back(plane); }

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

void Company::readFlight() {
    std::ifstream f;

    f.open(FLIGHT_FILE_PATH);
    if (f.fail())
        throw ReadError();
    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);
        parsedLine = split(line, '\t');
        unsigned int num = std::strtoul(parsedLine.at(3).c_str(), nullptr, 10);
        unsigned int dur = std::strtoul(parsedLine.at(4).c_str(), nullptr, 10);
        Flight flight = Flight(parsedLine.at(0), parsedLine.at(1),
                               parsedLine.at(2), num, dur);
        for (auto p : this->getPlanes()) {
            if (std::to_string(p.getID()) == parsedLine.at(5))
                populateFlight(p, flight);
        }
        _flights.push_back(flight);
    }
    f.close();
}

void Company::readPlane() {
    std::ifstream f;

    f.open(PLANE_FILE_PATH);
    if (f.fail())
        throw ReadError();
    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);
        parsedLine = split(line, '\t');
        unsigned int cap = std::strtoul(parsedLine.at(2).c_str(), nullptr, 10);
        unsigned int id = std::strtoul(parsedLine.at(3).c_str(), nullptr, 10);
        Plane plane = Plane(parsedLine.at(0), parsedLine.at(1), cap, id);
        _planes.push_back(plane);
    }
    f.close();
}

void Company::readService() {
    std::ifstream f;

    f.open(SERVICE_FILE_PATH);
    if (f.fail())
        throw ReadError();
    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);
        parsedLine = split(line, '\t');
        unsigned int type = std::strtoul(parsedLine.at(0).c_str(), nullptr, 10);
        Service service = Service(type, parsedLine.at(1), parsedLine.at(2));
        for (auto p : this->getPlanes()) {
            if (std::to_string(p.getID()) == parsedLine.at(3))
                p.addService(service);
        }
    }
    f.close();
}

void Company::readClient() {
    std::ifstream f;

    f.open(CLIENT_FILE_PATH);
    if (f.fail())
        throw ReadError();
    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);
        parsedLine = split(line, '\t');
        Client client = Client(parsedLine.at(0), std::stoul(parsedLine.at(1)));
        std::vector<std::pair<int, int>> parsedClientTickets =
            parseClientTickets(parsedLine.at(2));
        for (auto p : parsedClientTickets) {
            Ticket ticket = Ticket(p.first, p.second);
            client.addFlight(ticket);
        }
        _clients.push_back(client);
    }

    f.close();
}

void Company::writeFlight() {
    std::ofstream of{FLIGHT_FILE_PATH};

    if (of.fail())
        throw ReadError();

    for (const Flight &f : _flights) {
        of << f.getOrigin() << '\t' << f.getDestination() << '\t'
           << f.getDepartureDate() << '\t' << f.getNumber() << '\t'
           << f.getDuration() << '\t';

        // TODO
        // for (const Plane &p : _planes)
        //     if (p.)
    }
}

void Company::writePlane() {
    std::ofstream of{PLANE_FILE_PATH};

    if (of.fail())
        throw ReadError();

    for (const Plane &p : _planes) {
        of << p.getPlate() << '\t' << p.getType() << '\t' << p.getCapacity()
           << '\t' << p.getID() << '\n';

        // TODO: Services
    }
}

void Company::writeClient() {
    std::ofstream of{CLIENT_FILE_PATH};

    if (of.fail())
        throw ReadError();

    for (const Client &c : _clients) {
        of << c.getName() << '\t' << c.getNIF() << '\t';

        bool first{true};
        for (const Ticket &t : c.getTickets()) {
            if (!first)
                of << ';';

            of << t.getID() << ',' << t.getFlightID();
        }

        of << '\n';
    }
}
