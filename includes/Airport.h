#ifndef AED_PROJ_2021_AIRPORT_H
#define AED_PROJ_2021_AIRPORT_H

class Airport;

#include "../includes/BST.h"
#include "../includes/Transport.h"

#include <string>

/**
 * @brief Represents an airport.
 */
class Airport {
    /**
     * @brief This airport's index in the Company::_airports vector.
     */
    unsigned _id;

    /**
     * @brief This airport's name.
     */
    std::string _name{};
    /**
     * @brief Land transports near this airport.
     */
    BST<Transport> _transports;

public:
    /**
     * @brief Creates a new airport.
     *
     * @note Don't call this directly, use Company::createAirport.
     *
     * @param id The airport's index in the Company::_airports vector.
     * @param name The airport name.
     */
    Airport(unsigned id, std::string name) : _id(id), _name(name){};

    /**
     * @return This airport's index in the Company::_airports vector.
     */
    unsigned getID() const { return _id; }
    /**
     * @return This airport's name.
     */
    std::string getName() const { return _name; };
    /**
     * @return Land transports near this airport.
     */
    BST<Transport> &getTransports() { return _transports; }
    /**
     * @brief Sets this airport's index in the Company::_airports vector.
     *
     * @param id The new index.
     */
    void setID(unsigned id) { _id = id; }
    /**
     * @brief Sets this airport's name.
     *
     * @param name The new name.
     */
    void setName(std::string name) { _name = name; }

    /**
     * @brief Adds a new land transport near this airport.
     *
     * @param t The transport to add.
     */
    void addTransport(const Transport &t) { _transports.insert(t); }
};

#endif // AED_PROJ_2021_AIRPORT_H
