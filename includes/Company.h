#ifndef AED_PROJ_2021_COMPANY_H
#define AED_PROJ_2021_COMPANY_H

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
    std::vector<Flight *> _flights{};
    std::vector<Plane *> _planes{};
    std::vector<Client *> _clients{};
    std::vector<Airport *> _airports{};
    std::vector<Cart *> _carts{};

    /**
     * @brief Loads airports from file.
     */
    void readAirport();

    /**
     * @brief Loads planes, their flights and their services from file.
     */
    void readPlane();

    /**
     * @brief Loads clients and their tickets from file.
     */
    void readClient();

    /**
     * @brief Writes the names of the airports to file.
     */
    void writeAirport();

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
     * @brief Calls the write functions to save the current company's data to
     * files.
     */
    void save();

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
     * @return all of this company's airports.
     */
    std::vector<Airport *> getAirports() const { return _airports; };

    /**
     * @return all of this company's lugagge carts.
     */
    std::vector<Cart *> getCarts() const { return _carts; };

    /**
     * @brief Iterates over the _carts vector to find the cart from flightID.
     *
     * @param flightID The ID of the flight to which the cart points at.
     * @return A pointer to the correspondent cart or nullptr if is does not
     * exist.
     */
    Cart *findCart(unsigned flightID);

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
     * @note Dealocates the pointer and sets it to null in the _clients vector.
     *
     * @param client The client to delete
     */
    void deleteClient(Client *client);

    /**
     * @brief Creates a new flight.
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
    void updateFlight(Flight *flight, unsigned duration, std::string origin,
                      std::string dest, std::string departure, unsigned plane);

    /**
     * @brief Deletes a flight.
     *
     * @note Dealocates the pointer and sets it to null in the _flights vector.
     *
     * @param flight The flight to delete.
     */
    void deleteFlight(Flight *flight);

    /**
     * @brief Creates a new plane.
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
    void updatePlane(Plane *plane, unsigned rows, unsigned columns);

    /**
     * @brief Deletes a plane.
     *
     * @note Dealocates the pointer and sets it to null in the _planes vector.
     *
     * @param plane The plane to delete.
     */
    void deletePlane(Plane *plane);

    /**
     * @brief Creates a new airport.
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
     * @note Dealocates the pointer and sets it to null in the _airports vector.
     *
     * @param airport The airport to delete.
     */
    void deleteAirport(Airport *airport);

    /**
     * @brief Iterates over the _flights vector to find the flight with
     * number.
     *
     * @param number The number of the flight that is being searched.
     * @return A pointer to the flight with the correspondent number or nullptr
     * if is does not exist.
     */
    Flight *findFlight(unsigned number);

    /**
     * @brief Iterates over the _clients vector to find the client with NIF.
     *
     * @param nif The NIF of the client that is being searched.
     * @return A pointer to the client with the correspondent NIF or nullptr if
     * is does not exist.
     */
    Client *findClient(unsigned nif);

    /**
     * @brief Iterates over the _planes vector to find the plane with id.
     *
     * @param id The id of the plane.
     * @return A pointer to the plane with the correspondent id or nullptr if is
     * does not exist.
     */
    Plane *findPlane(unsigned id);

    /**
     * @brief Iterates over the _airports vector to find the plane with name.
     *
     * @param name The name of the airport.
     * @return A pointer to the plane with the correspondent name or nullptr if
     * is does not exist.
     */
    Airport *findAirport(std::string name);

    void updateCart(Cart *cart, unsigned newCartSize, unsigned newTrolleySize,
                    unsigned newStackSize);
};

#endif // AED_PROJ_2021_COMPANY_H
