#ifndef AED_PROJ_2021_FLIGHT_H
#define AED_PROJ_2021_FLIGHT_H

class Flight;

#include "Airport.h"
#include "Cart.h"
#include "Luggage.h"
#include "Plane.h"
#include "Ticket.h"

#include <queue>
#include <string>
#include <vector>

/**
 * @brief Represents a flight.
 */
class Flight {
private:
    unsigned _id;

    const unsigned _number;
    unsigned _duration;
    std::vector<Ticket *> _tickets;
    std::vector<Luggage *> _storage;
    Airport *_destination, *_origin;
    std::string _departureDate;
    Plane *_plane = nullptr;

    void generateTickets();
    void deleteTickets();

public:
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
    /**
     * @return This flight's storage.
     */
    std::vector<Luggage *> getStorage() const { return _storage; };

    unsigned getAvailability() const;

    // Setters
    /**
     * @brief Sets this flight's duration.
     *
     * @param duration The new duration.
     */
    void setID(unsigned id) { _id = id; };
    /**
     * @brief Sets this flight's duration.
     *
     * @param duration The new duration.
     */
    void setDuration(unsigned dur) { _duration = dur; };
    /**
     * @brief Sets this flight's departure date.
     *
     * @param dep The new departure date.
     */
    void setDepartureDate(std::string dep) { _departureDate = dep; };
    /**
     * @brief Sets this flight's origin.
     *
     * @param origin The new origin.
     */
    void setOrigin(Airport *origin) { _origin = origin; };
    /**
     * @brief Sets this flight's destination.
     *
     * @param dest The new destination.
     */
    void setDestination(Airport *dest) { _destination = dest; };
    /**
     * @brief Sets this flight's plane.
     *
     * @param plane The new plane.
     */
    void setPlane(Plane *plane);

    /**
     * @brief Gets the ticket for the corresponding seat.
     *
     * @note Uses binary search, as the tickets are generated and stored in
     *       lexicographical order.
     *
     * @param seat The seat to search for.
     * @return A pointer to the ticket, if it was found, or nullptr otherwise.
     */
    Ticket *findTicketBySeat(const std::string &seat);

    /**
     * @brief Adds luggage to the plane's storage, associated to the flight.
     *
     * @param luggage The luggage to be added.
     */
    void addLuggage(Luggage *luggage) { _storage.push_back(luggage); };
};

#endif // AED_PROJ_2021_FLIGHT_H
