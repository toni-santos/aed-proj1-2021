#ifndef AED_PROJ_2021_CLIENT_H
#define AED_PROJ_2021_CLIENT_H


#include <string>
#include <vector>
#include "Ticket.h"

class Client {
private:
    std::string _name;
    const unsigned _NIF; // id attribute
    std::vector<Ticket> _tickets;
public:
    Client(std::string name, unsigned NIF):
        _name(name), _NIF(NIF) {};

    // Getters
    unsigned getNIF() { return _NIF; };
    std::string getName() { return _name; };

    void addFlight(Ticket ticket) {
        _tickets.push_back(ticket);
    }
};


#endif //AED_PROJ_2021_CLIENT_H
