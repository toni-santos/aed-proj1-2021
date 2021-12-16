#ifndef AED_PROJ_2021_AIRPORT_H
#define AED_PROJ_2021_AIRPORT_H

class Airport;

#include "Transport.h"
// #include "bst.h"

#include <string>

/**
 * @brief Class representing an airport.
 */
class Airport {
    unsigned _id;

    std::string _name{};
    // TODO
    // BST<Transport> transports{};

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
