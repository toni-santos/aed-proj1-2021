#ifndef AED_PROJ_2021_PLANE_H
#define AED_PROJ_2021_PLANE_H

class Plane;

#include "Flight.h"
#include "Service.h"
#include <queue>

class Plane {
private:
    const unsigned _id;

    const std::string _plate, _type;
    std::queue<Flight *> _flights;
    unsigned _rows, _columns;
    std::queue<Service> _services, _servicesDone;

public:
    // Constructors
    Plane(unsigned id, unsigned rows, unsigned columns, std::string plate,
          std::string type)
        : _id(id), _rows(rows), _columns(columns), _plate(plate), _type(type){};
    ~Plane();

    // Getters
    unsigned getID() const { return _id; };
    unsigned getCapacity() const { return _rows * _columns; };
    unsigned getRows() const { return _rows; };
    unsigned getColumns() const { return _columns; };
    std::string getPlate() const { return _plate; };
    std::string getType() const { return _type; };
    std::queue<Flight *> getFlights() const { return _flights; };
    std::queue<Service> getServices() const { return _services; };
    std::queue<Service> getServicesDone() const { return _servicesDone; };

    // Setters
    void setRows(unsigned rows) { _rows = rows; };
    void setColumns(unsigned columns) { _columns = columns; };

    void addFlight(Flight *flight);

    void addService(Service serv);

    void doService();
};

#endif // AED_PROJ_2021_PLANE_H
