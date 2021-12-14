#ifndef AED_PROJ_2021_TICKET_H
#define AED_PROJ_2021_TICKET_H

class Ticket {
    const unsigned _id, _flightID;
    // TODO: prices (?)
public:
    Ticket(unsigned id, unsigned flightID) : _id(id), _flightID(flightID){};

    // Getters
    unsigned getID() const { return _id; };
    unsigned getFlightID() const { return _flightID; };
};

#endif // AED_PROJ_2021_TICKET_H
