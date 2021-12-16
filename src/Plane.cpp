//
// Created by ANTONIO on 11/25/2021.
//

#include "../includes/Plane.h"

Plane::~Plane() {}

void Plane::addFlight(Flight *flight) { _flights.push(flight); };

void Plane::addService(Service serv) { _services.push(serv); }

void Plane::doService() {
    _servicesDone.push(_services.front());
    _services.pop();
}