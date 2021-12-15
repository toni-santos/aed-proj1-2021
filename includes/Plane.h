#ifndef AED_PROJ_2021_PLANE_H
#define AED_PROJ_2021_PLANE_H

#include "Service.h"
#include <queue>

class Plane {
private:
    std::string _plate, _type;
    std::queue<unsigned> _flights;
    unsigned _capacity, _id;
    std::queue<Service> _services, _servicesDone;

public:
    // Constructors
    Plane() {
        _capacity = 0;
        _plate = "";
        _type = "";
    };

    Plane(std::string plate, std::string type, unsigned capacity, unsigned id) {
        _capacity = capacity;
        _plate = plate;
        _type = type;
        _id = id;
    };

    // Getters
    unsigned getCapacity() const { return _capacity; };
    unsigned  getID() const { return _id;};
    std::string getPlate() const { return _plate; };
    std::string getType() const { return _type; };
    std::queue<unsigned> getFlights() const { return _flights; };

    // Setters
    void setCapacity(unsigned cap) { _capacity = cap; }
    void setPlate(std::string pl) { _plate = pl; }
    void setType(std::string type) { _type = type; }
    void setId(unsigned id) { _id = id; }

    void addFlight(unsigned flightID) {
        _flights.push(flightID);
    };

    void addService(Service serv) {
        _services.push(serv);
    }

    void serviceDone(){
        _servicesDone.push(_services.front());
        _services.pop();
    }
};


#endif //AED_PROJ_2021_PLANE_H
