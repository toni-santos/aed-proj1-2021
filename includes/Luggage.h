#ifndef AED_PROJ_2021_LUGGAGE_H
#define AED_PROJ_2021_LUGGAGE_H

class Luggage;

#include "Client.h"

class Luggage {
    const Client *_owner;

public:
    Luggage(Client *owner) : _owner(owner){};

    /**
     * @return A pointer to the client associated to the luggage (its owner).
     */
    const Client *getOwner() const { return _owner; };
};

#endif // AED_PROJ_2021_LUGGAGE_H