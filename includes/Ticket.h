#ifndef AED_PROJ_2021_TICKET_H
#define AED_PROJ_2021_TICKET_H

class Ticket;

#include "Client.h"
#include "Flight.h"
#include "Luggage.h"

#include <string>

/**
 * @brief Represents a ticket for a flight.
 */
class Ticket {
    const Flight *_flight;
    const std::string _seat;
    Client *_client = nullptr;
    Luggage *_luggage = nullptr;

public:
    Ticket(Flight *flight, std::string seat) : _flight(flight), _seat(seat){};
    ~Ticket();

    // Getters
    /**
     * @return This ticket's flight.
     */
    const Flight *getFlight() const { return _flight; };
    /**
     * @return This ticket's seat.
     */
    std::string getSeat() const { return _seat; };
    /**
     * @return This ticket's client.
     */
    Client *getClient() const { return _client; };

    /**
     * @brief Set this ticket's client.
     *
     * @param client The new client.
     */
    void setClient(Client *client) {
        _luggage = nullptr;
        _client = client;
    };

    /**
     * @brief Associate a luggage to this ticket.
     *
     * @param luggage The luggage to be linked.
     */
    void addLuggage(Luggage *luggage) { _luggage = luggage; };
};

#endif // AED_PROJ_2021_TICKET_H
