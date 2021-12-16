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

void Flight::deleteTickets() {
    for (Ticket *ticket : _tickets)
        delete ticket;

    _tickets.resize(0);
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

// TODO: FIX THIS FUNCITON - error: no match for ‘operator<’ (operand types are
// ‘Ticket*’ and ‘const Ticket’)
bool operator<(const Ticket *ticket, const std::string &seat) {
    return ticket->getSeat() < seat;
}

Ticket *Flight::findTicketBySeat(const std::string &seat) {
    size_t begin{0}, end{_tickets.size() - 1};

    while (begin < end) {
        size_t middle{(begin + end) / 2};

        if (_tickets.at(middle) < seat) {
            begin = middle + 1;
        } else {
            end = middle;
        }
    }

    Ticket *ticket{_tickets.at(begin)};
    return ticket->getSeat() != seat ? nullptr : ticket;
}
