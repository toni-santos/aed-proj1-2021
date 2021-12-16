#ifndef AED_PROJ_2021_TICKET_H
#define AED_PROJ_2021_TICKET_H

class Ticket;

#include "Client.h"
#include "Flight.h"

#include <string>

class Ticket {
    const Flight *_flight;
    const std::string _seat;
    Client *_client = nullptr;
    // TODO: prices (?)
public:
    Ticket(Flight *flight, std::string seat) : _flight(flight), _seat(seat){};
    ~Ticket();

    // Getters
    const Flight *getFlight() const { return _flight; };
    std::string getSeat() const { return _seat; };
    Client *getClient() const { return _client; };

    void setClient(Client *client) { _client = client; }

    bool operator<(const Ticket &other) { return _seat < other._seat; }
};

#endif // AED_PROJ_2021_TICKET_H
