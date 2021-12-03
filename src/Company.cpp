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
        parsedLine = split(line);
        if (parsedLine[0] == "flight"){
            unsigned int  num = std::strtoul(parsedLine.at(4).c_str(),nullptr, 10);
            unsigned int  dur = std::strtoul(parsedLine.at(5).c_str(),nullptr, 10);
            Flight flight = Flight(parsedLine[1],parsedLine[2],parsedLine[3],num,dur);
            //std::cout << flight.getNumber() << " " << flight.getDepartureDate() << " " << flight.getDestination() << " " << flight.getDuration() << " " << flight.getOrigin() << std::endl;
        } else {
            unsigned int  cap = std::strtoul(parsedLine.at(3).c_str(),nullptr, 10);
            unsigned int  id = std::strtoul(parsedLine.at(4).c_str(),nullptr, 10);
            Plane plane = Plane(parsedLine[1],parsedLine[2],cap,id);
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