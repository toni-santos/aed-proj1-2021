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
    /**
     * @brief The flight this ticket is associated with.
     */
    const Flight *_flight;
    /**
     * @brief Which seat this ticket is for.
     */
    const std::string _seat;
    /**
     * @brief Who has bought this ticket.
     */
    Client *_client = nullptr;
    /**
     * @brief Luggage associated with this ticket.
     */
    Luggage *_luggage = nullptr;

public:
    /**
     * @brief Creates a new ticket.
     *
     * @param flight The flight to associate this ticket with.
     * @param seat The seat the ticket is for.
     */
    Ticket(Flight *flight, std::string seat) : _flight(flight), _seat(seat){};
    ~Ticket();

    // Getters
    /**
     * @return The flight this ticket is associated with.
     */
    const Flight *getFlight() const { return _flight; };
    /**
     * @return Which seat this ticket is for.
     */
    std::string getSeat() const { return _seat; };
    /**
     * @return Who has bought this ticket.
     */
    Client *getClient() const { return _client; };
    /**
     * @return Luggage associated with this ticket.
     */
    Luggage *getLuggage() const { return _luggage; };

    /**
     * @brief Change who has bought this client.
     *
     * @note Also removes any luggage associated with this ticket.
     *
     * @param client The new client.
     */
    void setClient(Client *client) {
        _luggage = nullptr;
        _client = client;
    };

    /**
     * @brief Associate luggage with this ticket.
     *
     * @param luggage The luggage.
     */
    void addLuggage(Luggage *luggage) { _luggage = luggage; };
};

#endif // AED_PROJ_2021_TICKET_H
