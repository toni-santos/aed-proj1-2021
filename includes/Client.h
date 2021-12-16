#ifndef AED_PROJ_2021_CLIENT_H
#define AED_PROJ_2021_CLIENT_H

class Client;

#include "Ticket.h"

#include <string>
#include <vector>

class Client {
private:
    const unsigned _id;

    const unsigned _nif{}; // id attribute
    std::string _name{};
    std::vector<Ticket *> _tickets{};

public:
    Client(unsigned id, unsigned nif, std::string name)
        : _id(id), _nif(nif), _name(name){};
    ~Client();

    // Setters
    void setName(std::string name) { _name = name; }

    // Getters
    unsigned getID() const { return _id; }
    unsigned getNIF() const { return _nif; }
    std::string getName() const { return _name; }
    std::vector<Ticket *> getTickets() const { return _tickets; }

    void addTicket(Ticket *ticket) { _tickets.push_back(ticket); }

    bool operator==(const Client c2) { return (this->getNIF() == c2.getNIF()); }
};

#endif // AED_PROJ_2021_CLIENT_H
