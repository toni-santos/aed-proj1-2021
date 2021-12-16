#include "../includes/Plane.h"

Plane::~Plane() {}

void Plane::addFlight(Flight *flight) { _flights.push_back(flight); }

void Plane::removeFlight(Flight *flight) { _flights.remove(flight); }

void Plane::addService(Service serv) { _services.push_back(serv); }

void Plane::doService() {
    _servicesDone.push_back(_services.front());
    _services.pop_front();
}