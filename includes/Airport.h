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
    unsigned _id;

    std::string _name{};
    BST<Transport> _transports;

public:
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
    BST<Transport> getTransports() const { return _transports; }
    /**
     * @brief Set this airport's id.
     *
     * @param id The new id.
     */
    void setID(unsigned id) { _id = id; }
    /**
     * @brief Set this airport's name.
     *
     * @param name The new name.
     */
    void setName(std::string name) { _name = name; }
};

#endif // AED_PROJ_2021_AIRPORT_H
