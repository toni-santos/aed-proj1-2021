#include <iostream>
#include "../includes/Company.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"

Company::Company() {
    populate();
}

void Company::populate() {
    std::ifstream i;

    i.open(companyPath);
    while (!i.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(i, line);
        parsedLine = split(line, ' ');
        if (parsedLine[0]=="#") continue;
        if (parsedLine[0] == "flight"){
            unsigned int  num = std::strtoul(parsedLine.at(4).c_str(),nullptr, 10);
            unsigned int  dur = std::strtoul(parsedLine.at(5).c_str(),nullptr, 10);
            Flight flight = Flight(parsedLine[1],parsedLine[2],parsedLine[3],num,dur);
            for (auto p : this->getPlanes()) {
                if (std::to_string(p.getID()) == parsedLine[6]) addPlane(p,flight);
            }
            _flights.push_back(flight);
        } else if (parsedLine[0] == "plane") {
            unsigned int  cap = std::strtoul(parsedLine.at(3).c_str(),nullptr, 10);
            unsigned int  id = std::strtoul(parsedLine.at(4).c_str(),nullptr, 10);
            Plane plane = Plane(parsedLine[1],parsedLine[2],cap,id);
            _planes.push_back(plane);
        } else {
            unsigned int  type = std::strtoul(parsedLine.at(1).c_str(),nullptr, 10);
            Service service = Service(type, parsedLine[2], parsedLine[3]);
            for (auto p : this->getPlanes()) {
                if (std::to_string(p.getID()) == parsedLine[4]) p.addService(service);
            }
        }
    }
    i.close();
}

void Company::addPlane(Plane plane, Flight flight) {
    plane.addFlight(flight.getNumber());
    for (int i = 0; i < plane.getCapacity(); i++) {
        flight.addTicket(Ticket(i, flight.getNumber()));
    }
}