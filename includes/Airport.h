#ifndef AED_PROJ_2021_AIRPORT_H
#define AED_PROJ_2021_AIRPORT_H

class Airport;

#include "Transport.h"
// #include "bst.h"

#include <string>

class Airport {
    const unsigned _id;

    std::string _name{};
    // TODO
    // BST<Transport> transports{};

public:
    Airport(unsigned id, std::string name) : _id(id), _name(name){};

    unsigned getID() const { return _id; }
    std::string getName() const { return _name; };
    void setName(std::string name) { _name = name; }
};

#endif // AED_PROJ_2021_AIRPORT_H
