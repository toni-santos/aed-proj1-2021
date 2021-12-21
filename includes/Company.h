#ifndef AED_PROJ_2021_COMPANY_H
#define AED_PROJ_2021_COMPANY_H

class Company;

#include "Airport.h"
#include "Cart.h"
#include "Client.h"
#include "Flight.h"

#include <fstream>

/**
 * @brief Represents the airline company.
 */
class Company {
private:
    /**
     * @brief All the planes that belong to this company.
     */
    std::vector<Plane *> _planes{};
    /**
     * @brief All the flights this company operates.
     */
    std::vector<Flight *> _flights{};
    /**
     * @brief All the clients that have used this company.
     */
    std::vector<Client *> _clients{};
    /**
     * @brief All the airports this company operates at.
     */
    std::vector<Airport *> _airports{};

    /**
     * @brief Loads all planes, their flights and their services from file.
     */
    void readPlane();
    /**
     * @brief Loads all airports and the land transports near them from file.
     */
    void readAirport();
    /**
     * @brief Loads all clients and their tickets from file.
     */
    void readClient();

    /**
     * @brief Writes all planes, their flights and their services to file.
     */
    void writePlane();
    /**
     * @brief Writes all airports and the land transports near them to file.
     */
    void writeAirport();
    /**
     * @brief Writes all clients and their tickets to file.
     */
    void writeClient();

public:
    /**
     * @brief Populates this company with data from files.
     */
    void populate();
    /**
     * @brief Calls the write functions to save the current company's data to
     * files.
     */
    void save();

    /**
     * @return All the planes that belong to this company.
     */
    std::vector<Plane *> getPlanes() const { return _planes; };
    /**
     * @return All the flights this company operates.
     */
    std::vector<Flight *> getFlights() const { return _flights; };
    /**
     * @return All the clients that have used this company.
     */
    std::vector<Client *> getClients() const { return _clients; };
    /**
     * @return All the airports this company operates at.
     */
    std::vector<Airport *> getAirports() const { return _airports; };

    /**
     * @brief Creates a new plane.
     *
     * @details Also adds the plane to the _planes vector and sets its ID to
     *          the correct value.
     *
     * @param rows The new plane's rows.
     * @param columns The new plane's columns.
     * @param plate The new plane's plate.
     * @param type The new plane's type.
     * @return A pointer to the newly created plane.
     */
    Plane *createPlane(unsigned rows, unsigned columns, std::string plate,
                       std::string type);
    /**
     * @brief Updates a plane with new information.
     *
     * @note If a string argument is left empty it won't be changed.
     *       The same applies when an unsigned argument is equal to 0.
     *       (IDs will always change the value.)
     *
     * @param plane The plane to update.
     * @param rows The new rows.
     * @param columns The new columns.
     */
    void updatePlane(Plane *plane, unsigned rows, unsigned columns);
    /**
     * @brief Deletes a plane.
     *
     * @details Also removes the plane from the _planes vector and updates every
     *          other plane's ID.
     *
     * @param plane The plane to delete.
     */
    void deletePlane(Plane *plane);

    /**
     * @brief Creates a new flight.
     *
     * @details Also adds the flight to the _flights vector and sets its ID to
     *          the correct value.
     *
     * @param number The new flight's number.
     * @param duration The new flight's duration.
     * @param origin The new flight's origin.
     * @param dest The new flight's destination.
     * @param departure The new flight's departure date.
     * @param plane The new flight's plane.
     * @return A pointer to the newly created flight.
     */
    Flight *createFlight(unsigned number, unsigned duration, Airport *origin,
                         Airport *dest, std::string departure, Plane *plane);
    /**
     * @brief Updates a flight with new information.
     *
     * @note If a string argument is left empty it won't be changed.
     *       The same applies when an unsigned argument is equal to 0.
     *       (IDs will always change the value.)
     *
     * @param flight The flight to update.
     * @param duration The new duration.
     * @param origin The new origin.
     * @param dest The new destination.
     * @param departure The new departure date.
     * @param plane The ID of new plane.
     */
    void updateFlight(Flight *flight, unsigned duration, std::string origin,
                      std::string dest, std::string departure, unsigned plane);
    /**
     * @brief Deletes a flight.
     *
     * @details Also removes the flight from the _flights vector and updates
     *          every other flight's ID.
     *
     * @param flight The flight to delete.
     */
    void deleteFlight(Flight *flight);

    /**
     * @brief Creates a new client.
     *
     * @details Also adds the client to the _clients vector and sets its ID to
     *          the correct value.
     *
     * @param nif The new client's NIF.
     * @param name The new client's name.
     * @return A pointer to the newly created client.
     */
    Client *createClient(unsigned nif, std::string name);
    /**
     * @brief Updates a client with new information.
     *
     * @note If a string argument is left empty it won't be changed.
     *       The same applies when an unsigned argument is equal to 0.
     *       (IDs will always change the value.)
     *
     * @param client The client to update.
     * @param name The new name.
     */
    void updateClient(Client *client, std::string name);
    /**
     * @brief Deletes a client.
     *
     * @details Also removes the client from the _clients vector and updates
     *          every other client's ID.
     *
     * @param client The client to delete
     */
    void deleteClient(Client *client);

    /**
     * @brief Creates a new airport.
     *
     * @details Also adds the airport to the _airports vector and sets its ID
     * to the correct value.
     *
     * @param name The new airport's name.
     * @return A pointer to the newly created airport.
     */
    Airport *createAirport(std::string name);
    /**
     * @brief Updates an airport with new information.
     *
     * @note If a string argument is left empty it won't be changed.
     *       The same applies when an unsigned argument is equal to 0.
     *       (IDs will always change the value.)
     *
     * @param airport The airport to update.
     * @param name The new name.
     */
    void updateAirport(Airport *airport, std::string name);
    /**
     * @brief Deletes an airport.
     *
     * @details Also removes the airport from the _airports vector and updates
     *          every other airport's ID.
     *
     * @param airport The airport to delete.
     */
    void deleteAirport(Airport *airport);

    /**
     * @brief Finds a flight by its number.
     *
     * @param number The number of the flight we want to find.
     * @return A pointer to the flight if found.
     * @return nullptr otherwise.
     */
    Flight *findFlight(unsigned number);
    /**
     * @brief Finds a client by its NIF.
     *
     * @param nif The NIF of the client we want to find.
     * @return A pointer to the client if found.
     * @return nullptr otherwise.
     */
    Client *findClient(unsigned nif);
    /**
     * @brief Finds an airport by its name.
     *
     * @param name The name of the airport we want to find.
     * @return A pointer to the airport if found.
     * @return nullptr otherwise.
     */
    Airport *findAirport(std::string name);
};

#endif // AED_PROJ_2021_COMPANY_H
