#ifndef AED_PROJ_2021_PLANE_H
#define AED_PROJ_2021_PLANE_H

class Plane;

#include "Flight.h"
#include "Service.h"
#include <queue>

/**
 * @brief Class representing a plane.
 */
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
    /**
     * @return This plane's index in the Company::_planes vector.
     */
    unsigned getID() const { return _id; };
    /**
     * @return This plane's max capacity.
     */
    unsigned getCapacity() const { return _rows * _columns; };
    /**
     * @return This plane's rows.
     */
    unsigned getRows() const { return _rows; };
    /**
     * @return This plane's columns.
     */
    unsigned getColumns() const { return _columns; };
    /**
     * @return This plane's plate.
     */
    std::string getPlate() const { return _plate; };
    /**
     * @return This plane's type.
     */
    std::string getType() const { return _type; };
    /**
     * @return This plane's flights.
     */
    std::queue<Flight *> getFlights() const { return _flights; };
    /**
     * @return This plane's services that need to be done.
     */
    std::queue<Service> getServices() const { return _services; };
    /**
     * @return This plane's services that have been done.
     */
    std::queue<Service> getServicesDone() const { return _servicesDone; };

    // Setters
    /**
     * @brief Set this plane's rows.
     *
     * @param rows The new rows.
     */
    void setRows(unsigned rows) { _rows = rows; };
    /**
     * @brief Set this plane's columns.
     *
     * @param columns The new columns.
     */
    void setColumns(unsigned columns) { _columns = columns; };

    void addFlight(Flight *flight);

    void addService(Service serv);

    void doService();
};

#endif // AED_PROJ_2021_PLANE_H
