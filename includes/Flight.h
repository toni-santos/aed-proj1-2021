#ifndef AED_PROJ_2021_FLIGHT_H
#define AED_PROJ_2021_FLIGHT_H

class Flight;

#include "Airport.h"
#include "Plane.h"
#include "Ticket.h"

#include <queue>
#include <string>
#include <vector>

class Flight {
private:
    const unsigned _id;
    const unsigned _number;
    unsigned _duration;
    std::vector<Ticket *> _tickets;
    Airport *_destination, *_origin;
    std::string _departureDate;
    Plane *_plane;

    void generateTickets();
    void deleteTickets();

public:
    // Constructors
    // TODO: prices (?)
    Flight(unsigned id, unsigned number, unsigned duration, Airport *origin,
           Airport *dest, std::string departureDate, Plane *plane);
    ~Flight();

    // Getters
    unsigned getID() const { return _id; };
    unsigned getNumber() const { return _number; };
    unsigned getDuration() const { return _duration; };
    std::string getDepartureDate() const { return _departureDate; };
    Airport *getDestination() const { return _destination; };
    Airport *getOrigin() const { return _origin; };
    Plane *getPlane() const { return _plane; };

    // Setters
    void setDuration(unsigned dur) { _duration = dur; };
    void setDepartureDate(std::string dep) { _departureDate = dep; };
    void setOrigin(Airport *origin) { _origin = origin; };
    void setDestination(Airport *dest) { _destination = dest; };
    void setPlane(Plane *plane);

    Ticket *findTicketBySeat(const std::string &seat);
};

#endif // AED_PROJ_2021_FLIGHT_H
