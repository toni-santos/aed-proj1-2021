#ifndef AED_PROJ_2021_FLIGHT_H
#define AED_PROJ_2021_FLIGHT_H

#include <string>
#include <queue>
#include "Ticket.h"
#include "Plane.h"

class Flight {
private:
    const unsigned _number;
    unsigned _duration;
    std::queue<Ticket> _tickets;
    const std::string _destination, _origin;
    std::string _departureDate;
    const Plane _plane;

public:
    // Constructors
    // TODO: prices (?)
    Flight(std::string origin, std::string destination, std::string departureDate, unsigned number, unsigned duration):
        _origin(origin), _destination(destination), _departureDate(departureDate), _number(number), _duration(duration) { };

    // Getters
    unsigned getNumber() const { return _number; };
    unsigned getDuration() const { return _duration; };
    std::string getDepartureDate() const { return _departureDate; };
    std::string getDestination() const { return _destination; };
    std::string getOrigin() const { return _origin; };

    // Setters
    void setDuration(unsigned dur) { _duration = dur; };
    void setDepartureDate(std::string dep) { _departureDate = dep; };

    void addTicket(Ticket ticket) {
        _tickets.push(ticket);
    }
};


#endif //AED_PROJ_2021_FLIGHT_H
