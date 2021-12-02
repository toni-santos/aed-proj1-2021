//
// Created by ANTONIO on 12/2/2021.
//

#ifndef AED_PROJ_2021_TICKET_H
#define AED_PROJ_2021_TICKET_H


#include "Plane.h"

class Ticket {
    unsigned id;
    const unsigned _price;
    Plane plane;

public:
    Ticket(Plane plane, unsigned id, unsigned price): _price(price) {
        this->plane = plane;
        this->id = id;
    }

    // Getters
    unsigned getID() const { return this->id; }
    unsigned getPrice() const { return this->_price; }
    Plane getPlane() {return this->plane; }

    // Setters
    void setIO(unsigned id) { this->id = id; }
    void setPlane(Plane plane) { this->plane = plane; }

};


#endif //AED_PROJ_2021_TICKET_H
