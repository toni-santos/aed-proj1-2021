#include "../includes/Company.h"
#include "../includes/Exceptions.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
#include <iostream>

Company::Company() { populate(); }

void Company::populate() {
    readPlane();
    readFlight();
    readService();
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
        parsedLine = split(line, ' ');
        unsigned int num = std::strtoul(parsedLine.at(4).c_str(), nullptr, 10);
        unsigned int dur = std::strtoul(parsedLine.at(5).c_str(), nullptr, 10);
        Flight flight =
            Flight(parsedLine[1], parsedLine[2], parsedLine[3], num, dur);
        for (auto p : this->getPlanes()) {
            if (std::to_string(p.getID()) == parsedLine[6])
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
        parsedLine = split(line, ' ');
        unsigned int cap = std::strtoul(parsedLine.at(3).c_str(), nullptr, 10);
        unsigned int id = std::strtoul(parsedLine.at(4).c_str(), nullptr, 10);
        Plane plane = Plane(parsedLine[1], parsedLine[2], cap, id);
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
        parsedLine = split(line, ' ');
        unsigned int type = std::strtoul(parsedLine.at(1).c_str(), nullptr, 10);
        Service service = Service(type, parsedLine[2], parsedLine[3]);
        for (auto p : this->getPlanes()) {
            if (std::to_string(p.getID()) == parsedLine[4])
                p.addService(service);
        }
    }
    f.close();
}

void Company::addPlane(Plane plane, Flight flight) {
    plane.addFlight(flight.getNumber());
    for (int i = 0; i < plane.getCapacity(); i++) {
        flight.addTicket(Ticket(i, flight.getNumber()));
    }
}