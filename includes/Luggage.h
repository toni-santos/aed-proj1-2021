#ifndef AED_PROJ_2021_LUGGAGE_H
#define AED_PROJ_2021_LUGGAGE_H

class Luggage;

#include "Ticket.h"

/**
 * @brief Represents a piece of luggage.
 */
class Luggage {
    const Ticket *_ticket;

public:
    Luggage(Ticket *ticket) : _ticket(ticket){};

    /**
     * @return A pointer to the ticket associated to the luggage.
     */
    const Ticket *getTicket() const { return _ticket; };
};

#endif // AED_PROJ_2021_LUGGAGE_H