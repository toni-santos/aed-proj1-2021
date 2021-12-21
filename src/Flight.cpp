#include "../includes/Flight.h"
#include "../includes/Utils.h"

#include <algorithm>
#include <cmath>

void Flight::generateTickets() {
    unsigned columns = _plane->getColumns();
    unsigned width = numberLength(columns);
    char *seat = new char[width + 2];
    std::string format{"%c%0" + std::to_string(width) + "u"};

    for (unsigned r{0}; r < _plane->getRows(); ++r)
        for (unsigned c{1}; c <= _plane->getColumns(); ++c) {
            sprintf(seat, format.c_str(), 'A' + r, c);

            _tickets.push_back(new Ticket(this, {seat}));
        }

    delete[] seat;
}

void Flight::deleteTickets() {
    for (Ticket *ticket : _tickets)
        delete ticket;

    _tickets.resize(0);
}

Flight::Flight(unsigned id, unsigned number, unsigned duration, Airport *origin,
               Airport *dest, std::string departureDate, Plane *plane)
    : _id(id), _number(number), _origin(origin), _destination(dest),
      _departureDate(departureDate), _duration(duration),
      _cart(new Cart(this)) {
    setPlane(plane);
};

Flight::~Flight() {
    deleteTickets();

    delete _cart;

    for (Luggage *luggage : _storage)
        delete luggage;
};

void Flight::setPlane(Plane *plane) {
    if (_plane)
        _plane->removeFlight(this);
    plane->addFlight(this);

    _plane = plane;

    deleteTickets();
    generateTickets();
}

Ticket *Flight::findTicketBySeat(const std::string &seat) {
    size_t begin{0}, end{_tickets.size() - 1};

    Ticket *ticket;
    while (begin <= end) {
        size_t middle{(begin + end) / 2};
        ticket = _tickets.at(middle);

        if (ticket->getSeat() == seat)
            return ticket;
        else if (ticket->getSeat() < seat)
            begin = middle + 1;
        else
            end = middle - 1;
    }

    return nullptr;
}

unsigned Flight::getAvailability() const {
    int num = _tickets.size();
    for (auto ticket : _tickets) {
        if (ticket->getClient() != nullptr) {
            num--;
        }
    }

    return num;
}