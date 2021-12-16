#ifndef AED_PROJ_2021_FLIGHT_H
#define AED_PROJ_2021_FLIGHT_H

class Flight;

#include "Airport.h"
#include "Plane.h"
#include "Ticket.h"

#include <queue>
#include <string>
#include <vector>

/**
 * @brief Class representing a flight.
 */
class Flight {
private:
    unsigned _id;

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
    /**
     * @return This flight's index in the Company::_flights vector.
     */
    unsigned getID() const { return _id; };
    /**
     * @return This flight's number.
     */
    unsigned getNumber() const { return _number; };
    /**
     * @return This flight's duration.
     */
    unsigned getDuration() const { return _duration; };
    /**
     * @return This flight's departure date.
     */
    std::string getDepartureDate() const { return _departureDate; };
    /**
     * @return This flight's destination.
     */
    Airport *getDestination() const { return _destination; };
    /**
     * @return This flight's origin.
     */
    Airport *getOrigin() const { return _origin; };
    /**
     * @return This flight's plane.
     */
    Plane *getPlane() const { return _plane; };
    /**
     * @return This flight's tickets.
     */
    std::vector<Ticket *> getTickets() const { return _tickets; };

    unsigned getAvailability() const;

    // Setters
    /**
     * @brief Set this flight's duration.
     *
     * @param duration The new duration.
     */
    void setID(unsigned id) { _id = id; };
    /**
     * @brief Set this flight's duration.
     *
     * @param duration The new duration.
     */
    void setDuration(unsigned dur) { _duration = dur; };
    /**
     * @brief Set this flight's departure date.
     *
     * @param dep The new departure date.
     */
    void setDepartureDate(std::string dep) { _departureDate = dep; };
    /**
     * @brief Set this flight's origin.
     *
     * @param origin The new origin.
     */
    void setOrigin(Airport *origin) { _origin = origin; };
    /**
     * @brief Set this flight's destination.
     *
     * @param dest The new destination.
     */
    void setDestination(Airport *dest) { _destination = dest; };
    /**
     * @brief Set this flight's plane.
     *
     * @param plane The new plane.
     */
    void setPlane(Plane *plane);

    /**
     * @brief Get's the ticket for the corresponding seat.
     *
     * @note Uses binary search, as the tickets are generated and stored in
     *       lexicographical order.
     *
     * @param seat The seat to search for.
     * @return The ticket, if it was found.
     */
    Ticket *findTicketBySeat(const std::string &seat);
};

#endif // AED_PROJ_2021_FLIGHT_H
