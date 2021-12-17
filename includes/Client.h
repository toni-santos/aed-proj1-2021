#ifndef AED_PROJ_2021_CLIENT_H
#define AED_PROJ_2021_CLIENT_H

class Client;

#include "Ticket.h"

#include <string>
#include <vector>

/**
 * @brief Class representing a client.
 */
class Client {
private:
    const unsigned _id;

    const unsigned _nif{};
    std::string _name{};
    std::vector<Ticket *> _tickets{};

public:
    Client(unsigned id, unsigned nif, std::string name)
        : _id(id), _nif(nif), _name(name){};
    ~Client();

    // Setters
    /**
     * @brief Set this client's name.
     *
     * @param name The new name.
     */
    void setName(std::string name) { _name = name; }

    // Getters
    /**
     * @return This client's index in the Company::_clients vector.
     */
    unsigned getID() const { return _id; }
    /**
     * @return This client's NIF.
     */
    unsigned getNIF() const { return _nif; }
    /**
     * @return This client's name.
     */
    std::string getName() const { return _name; }
    /**
     * @return This client's tickets.
     */
    std::vector<Ticket *> getTickets() const { return _tickets; }

    /**
     * @brief associate a ticket to this client.
     *
     * @param ticket the ticket to be added.
     */
    void addTicket(Ticket *ticket) { _tickets.push_back(ticket); }
    /**
     * @brief remove a ticket from this client.
     *
     * @param ticket the ticket to be removed.
     */
    void removeTicket(Ticket *ticket);
    /**
     * @param c2 the client to be compared.
     * @return a boolean that verifies if this client's NIF is equal to another client's (c2's) NIF.
     */
    bool operator==(const Client c2) { return (this->getNIF() == c2.getNIF()); }
};

#endif // AED_PROJ_2021_CLIENT_H
