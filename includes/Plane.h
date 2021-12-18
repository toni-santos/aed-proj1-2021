#ifndef AED_PROJ_2021_PLANE_H
#define AED_PROJ_2021_PLANE_H

class Plane;

#include "Flight.h"
#include "Service.h"
#include <list>

/**
 * @brief Class representing a plane.
 */
class Plane {
private:
    unsigned _id;

    const std::string _plate, _type;
    std::list<Flight *> _flights;
    unsigned _rows, _columns;
    std::list<Service> _services, _servicesDone;

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
    std::list<Flight *> getFlights() const { return _flights; };
    /**
     * @return This plane's services that need to be done.
     */
    std::list<Service> getServices() const { return _services; };
    /**
     * @return This plane's services that have been done.
     */
    std::list<Service> getServicesDone() const { return _servicesDone; };

    // Setters
    /**
     * @brief Sets this plane's id.
     *
     * @param rows The new id.
     */
    void setID(unsigned id) { _id = id; };
    /**
     * @brief Sets this plane's rows.
     *
     * @param rows The new rows.
     */
    void setRows(unsigned rows) { _rows = rows; };
    /**
     * @brief Sets this plane's columns.
     *
     * @param columns The new columns.
     */
    void setColumns(unsigned columns) { _columns = columns; };

    /**
     * @brief Adds a flight to this plane's schedule.
     *
     * @param flight The flight to be added.
     */
    void addFlight(Flight *flight);

    /**
     * @brief Removes a flight to this plane's schedule.
     *
     * @param flight The flight to be removed.
     */
    void removeFlight(Flight *flight);

    /**
     * @brief Adds a service to this plane.
     *
     * @param flight The service to be added.
     */
    void addService(Service serv);

    /**
     * @brief Marks the service in front of the _services list as done.
     *
     * @note It acomplishes this by adding the service to the _servicesDone list and removing it from the _services list.
     */
    void doService();
};

#endif // AED_PROJ_2021_PLANE_H
