#ifndef AED_PROJ_2021_CLIENT_H
#define AED_PROJ_2021_CLIENT_H

class Client;

#include "Ticket.h"

#include <string>
#include <vector>

/**
 * @brief Represents a client.
 */
class Client {
private:
    /**
     * @brief This client's index in the Company::_clients vector.
     */
    unsigned _id;

    /**
     * @brief This client's NIF.
     */
    const unsigned _nif{};
    /**
     * @brief This client's name.
     */
    std::string _name{};
    /**
     * @brief The tickets this client has bought.
     */
    std::vector<Ticket *> _tickets{};

public:
    /**
     * @brief Creates a new client.
     *
     * @note Don't call this directly, use Company::createClient.
     *
     * @param id The client's index in the Company::_clients vector.
     * @param nif The client's NIF.
     * @param name The client's name.
     */
    Client(unsigned id, unsigned nif, std::string name)
        : _id(id), _nif(nif), _name(name){};
    ~Client();

    // Setters
    /**
     * @brief Sets this client's index in the Company::_clients vector.
     *
     * @param id The new index.
     */
    void setID(unsigned id) { _id = id; }
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
     * @brief Adds a ticket to this client's bought tickets.
     *
     * @param ticket The ticket.
     */
    void addTicket(Ticket *ticket) { _tickets.push_back(ticket); }
    /**
     * @brief Removes a ticket from this client's bought tickets.
     *
     * @param ticket The ticket.
     */
    void removeTicket(Ticket *ticket);
    /**
     * @brief Checks if two clients have the same NIF.
     *
     * @param other The other client.
     * @return true if both clients have the same NIF.
     * @return false otherwise.
     */
    bool operator==(const Client &other) { return _nif == other._nif; }
};

#endif // AED_PROJ_2021_CLIENT_H
