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
};


#endif //AED_PROJ_2021_COMPANY_H
