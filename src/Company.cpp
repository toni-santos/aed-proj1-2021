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

void Company::addPlane(Plane plane, Flight flight) {
    plane.addFlight(flight.getNumber());
    for (int i = 0; i < plane.getCapacity(); i++) {
        flight.addTicket(Ticket(i, flight.getNumber()));
    }
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
        unsigned int num = std::strtoul(parsedLine.at(4).c_str(), nullptr, 10);
        unsigned int dur = std::strtoul(parsedLine.at(5).c_str(), nullptr, 10);
        Flight flight = Flight(parsedLine.at(1), parsedLine.at(2),
                               parsedLine.at(3), num, dur);
        for (auto p : this->getPlanes()) {
            if (std::to_string(p.getID()) == parsedLine.at(6))
                addPlane(p, flight);
        }
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
        unsigned int cap = std::strtoul(parsedLine.at(3).c_str(), nullptr, 10);
        unsigned int id = std::strtoul(parsedLine.at(4).c_str(), nullptr, 10);
        Plane plane = Plane(parsedLine.at(1), parsedLine.at(2), cap, id);
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
        unsigned int type = std::strtoul(parsedLine.at(1).c_str(), nullptr, 10);
        Service service = Service(type, parsedLine.at(2), parsedLine.at(3));
        for (auto p : this->getPlanes()) {
            if (std::to_string(p.getID()) == parsedLine.at(4))
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
        Client client = Client(parsedLine.at(1), std::stoul(parsedLine.at(2)));
        std::vector<std::pair<int, int>> parsedClientTickets =
            parseClientTickets(parsedLine.at(3));
        for (auto p : parsedClientTickets) {
            Ticket ticket = Ticket(p.first, p.second);
            client.addFlight(ticket);
        }
        _clients.push_back(client);
    }

    f.close();
}
