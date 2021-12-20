#ifndef AED_PROJ_2021_PLANE_H
#define AED_PROJ_2021_PLANE_H

class Plane;

#include "Flight.h"
#include "Service.h"
#include <list>

/**
 * @brief Represents a plane.
 */
class Plane {
private:
    /**
     * @brief This plane's index in the Company::_planes vector.
     */
    unsigned _id;

    /**
     * @brief This plane's registration plate.
     */
    const std::string _plate;
    /**
     * @brief This plane's type.
     */
    const std::string _type;
    /**
     * @brief This plane's flight plan.
     */
    std::list<Flight *> _flights;
    /**
     * @brief How many rows of seats this plane has.
     */
    unsigned _rows;
    /**
     * @brief How many columns of seats this plane has.
     */
    unsigned _columns;
    /**
     * @brief The services this plane has scheduled.
     */
    std::list<Service> _services;
    /**
     * @brief The services that have been done to this plane.
     */
    std::list<Service> _servicesDone;

public:
    // Constructors
    /**
     * @brief Creates a new plane.
     *
     * @note Don't call this directly, use Company::createPlane.
     *
     * @param id The plane's index in the Company::_planes vector.
     * @param rows How many rows of seats the plane has.
     * @param columns How many columns of seats the plane has.
     * @param plate The plane's registration plate.
     * @param type The plane's type.
     */
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
     * @return How many rows of seats this plane has.
     */
    unsigned getRows() const { return _rows; };
    /**
     * @return How many columns of seats this plane has.
     */
    unsigned getColumns() const { return _columns; };
    /**
     * @return This plane's registration plate.
     */
    std::string getPlate() const { return _plate; };
    /**
     * @return This plane's type.
     */
    std::string getType() const { return _type; };
    /**
     * @return This plane's flight plan.
     */
    std::list<Flight *> getFlights() const { return _flights; };
    /**
     * @return The services this plane has scheduled.
     */
    std::list<Service> getServices() const { return _services; };
    /**
     * @return The services that have been done to this plane.
     */
    std::list<Service> getServicesDone() const { return _servicesDone; };

    // Setters
    /**
     * @brief Sets this plane's index in the Company::_planes vector.
     *
     * @param id The new index.
     */
    void setID(unsigned id) { _id = id; };
    /**
     * @brief Sets how many rows this plane has.
     *
     * @param rows The new amount of rows.
     */
    void setRows(unsigned rows) { _rows = rows; };
    /**
     * @brief Sets how many columns this plane has.
     *
     * @param columns The new amount of columns.
     */
    void setColumns(unsigned columns) { _columns = columns; };

    /**
     * @brief Adds a flight to this plane's plan.
     *
     * @param flight The flight to be added.
     */
    void addFlight(Flight *flight);

    /**
     * @brief Removes a flight to this plane's plan.
     *
     * @param flight The flight to be removed.
     */
    void removeFlight(Flight *flight);

    /**
     * @brief Adds a service to this plane's schedule.
     *
     * @param service The service to be added.
     */
    void addService(Service service);

    /**
     * @brief Does the next service in this plane's schedule.
     *
     * @details Also moves this service to the _servicesDone list.
     */
    void doService();
};

#endif // AED_PROJ_2021_PLANE_H
