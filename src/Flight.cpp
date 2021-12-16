//
// Created by toni on 03/12/21.
//

#include "../includes/Flight.h"

#include <algorithm>

void Flight::generateTickets() {
    unsigned columns = _plane->getColumns();
    unsigned width = columns / 10 + 1;
    char *seat = new char[width + 2];
    std::string format{"%c%0" + std::to_string(width) + "u"};

    for (unsigned c{1}; c <= _plane->getColumns(); ++c)
        for (unsigned r{0}; r < _plane->getRows(); ++r) {
            sprintf(seat, format.c_str(), 'A' + r, c);

            _tickets.push_back(new Ticket(this, {seat}));
        }

    delete[] seat;
}

Flight::Flight(unsigned id, unsigned number, unsigned duration, Airport *origin,
               Airport *dest, std::string departureDate, Plane *plane)
    : _id(id), _number(number), _origin(origin), _destination(dest),
      _departureDate(departureDate), _duration(duration), _plane(plane) {
    generateTickets();
};

Flight::~Flight() { deleteTickets(); };

void Flight::setPlane(Plane *plane) {
    _plane = plane;

    deleteTickets();
    generateTickets();
}

Ticket *Flight::findTicketBySeat(const std::string &seat) {
    auto it = std::lower_bound(_tickets.begin(), _tickets.end(),
                               Ticket(nullptr, seat));

    return it == _tickets.end() ? nullptr : *it;
}
