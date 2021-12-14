#ifndef AED_PROJ_2021_CLIENT_H
#define AED_PROJ_2021_CLIENT_H

#include "Ticket.h"
#include <string>
#include <vector>

class Client {
private:
    std::string _name;
    const unsigned _NIF; // id attribute
    std::vector<Ticket> _tickets;

public:
    Client(std::string name, unsigned NIF) : _name(name), _NIF(NIF){};

    // Getters
    unsigned getNIF() const { return _NIF; };
    std::string getName() const { return _name; };
    std::vector<Ticket> getTickets() const { return _tickets; };

    void addFlight(Ticket ticket) { _tickets.push_back(ticket); }
};

#endif // AED_PROJ_2021_CLIENT_H
