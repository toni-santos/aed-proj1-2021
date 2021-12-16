#ifndef AED_PROJ_2021_COMPANY_H
#define AED_PROJ_2021_COMPANY_H

#include "Airport.h"
#include "Client.h"
#include "Flight.h"

#include <fstream>

/**
 * @brief Class representing the airline company.
 */
class Company {
private:
    std::vector<Flight *> _flights{};
    std::vector<Plane *> _planes{};
    std::vector<Client *> _clients{};
    std::vector<Airport *> _airports{};

    /**
     * @brief Loads planes, their flights and their services from file.
     */
    void readPlane();

    /**
     * @brief Loads clients and their tickets from file.
     */
    void readClient();

    /**
     * @brief Writes the planes, their flights and their services to file.
     */
    void writePlane();

    /**
     * @brief Writes the clients and their tickets to file.
     */
    void writeClient();

public:
    /**
     * @brief Populates this company with data from files.
     */
    void populate();

    /**
     * @return All the flights operated by this company.
     */
    std::vector<Flight *> getFlights() const { return _flights; };

    /**
     * @return All the planes flown by this company.
     */
    std::vector<Plane *> getPlanes() const { return _planes; };

    /**
     * @return All the clients that have bought from this company.
     */
    std::vector<Client *> getClients() const { return _clients; };

    /**
     * @brief Creates a new client.
     *
     * @param nif The new client's NIF.
     * @param name The new client's name.
     * @return A pointer to the newly created client.
     */
    Client *createClient(unsigned nif, std::string name);

    /**
     * @brief Updates a client with new information.
     *
     * @note All arguments can be empty, at which point they won't be changed.
     *
     * @param client The client to update.
     * @param name The new name.
     */
    void updateClient(Client *client, std::string name);

    /**
     * @brief Deletes a client.
     *
     * Dealocates the pointer and sets it to null in the _clients vector.
     *
     * @param client The client to delete
     */
    void deleteClient(Client *client);

    /**
     * @brief Create a new flight.
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
     * @note All arguments can be empty, at which point they won't be changed.
     *
     * @param flight The flight to update.
     * @param duration The new duration.
     * @param origin The new origin.
     * @param dest The new destination.
     * @param departure The new departure date.
     * @param plane The new plane.
     */
    void updateFlight(Flight *flight, std::string duration, std::string origin,
                      std::string dest, std::string departure,
                      std::string plane);

    /**
     * @brief Deletes a flight.
     *
     * Dealocates the pointer and sets it to null in the _flights vector.
     *
     * @param flight The flight to delete
     */
    void deleteFlight(Flight *flight);

    /**
     * @brief Create a new plane.
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
     * @note All arguments can be empty, at which point they won't be changed.
     *
     * @param plane The plane to update.
     * @param rows The new rows.
     * @param columns The new columns.
     */
    void updatePlane(Plane *plane, std::string rows, std::string columns);

    /**
     * @brief Deletes a plane.
     *
     * Dealocates the pointer and sets it to null in the _planes vector.
     *
     * @param client The plane to delete
     */
    void deletePlane(Plane *plane);

    /**
     * @brief Create a new airport.
     *
     * @param name The new airport's name.
     * @return A pointer to the newly created airport.
     */
    Airport *createAirport(std::string name);

    /**
     * @brief Updates an airport with new information.
     *
     * @note All arguments can be empty, at which point they won't be changed.
     *
     * @param airport The airport to update.
     * @param name The new name.
     */
    void updateAirport(Airport *airport, std::string name);

    /**
     * @brief Deletes an airport.
     *
     * Dealocates the pointer and sets it to null in the _airports vector.
     *
     * @param client The airport to delete
     */
    void deleteAirport(Airport *airport);

    /**
     * @brief Iterates over the _flights vector to find the flight with
     * flightID.
     *
     * @param flightID The ID of the flight that is being searched
     */
    Flight *findFlight(unsigned number);

    /**
     * @brief Iterates over the _clients vector to find the client with NIF.
     *
     * @param flightID The NIF of the client that is being searched
     */
    Client *findClient(unsigned nif);

	Plane *findPlane(unsigned id);

	Airport *findAirport(std::string name);
};

#endif // AED_PROJ_2021_COMPANY_H
