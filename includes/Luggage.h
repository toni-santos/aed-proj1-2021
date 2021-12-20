#ifndef AED_PROJ_2021_LUGGAGE_H
#define AED_PROJ_2021_LUGGAGE_H

class Luggage;

#include "Ticket.h"

/**
 * @brief Represents a piece of luggage.
 */
class Luggage {
    /**
     * @brief The ticket this luggage is associated with.
     */
    const Ticket *_ticket;

public:
    /**
     * @brief Creates a new luggage.
     *
     * @param ticket The ticket to associate this luggage to.
     */
    Luggage(Ticket *ticket) : _ticket(ticket){};

    /**
     * @return The ticket this luggage is associated with.
     */
    const Ticket *getTicket() const { return _ticket; };
};

#endif // AED_PROJ_2021_LUGGAGE_H