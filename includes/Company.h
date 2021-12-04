#ifndef AED_PROJ_2021_COMPANY_H
#define AED_PROJ_2021_COMPANY_H

#include "Flight.h"

#include "fstream"

class Company {
private:
    std::vector<Flight> _flights;
    std::vector<Plane> _planes;
public:
    Company();

    void addPlane(Plane plane, Flight flight);

    void populate();

    std::vector<Flight> getFlights() { return _flights; };

    std::vector<Plane> getPlanes() { return _planes; };

};

#endif //AED_PROJ_2021_COMPANY_H
