#ifndef AED_PROJ_2021_COMPANY_H
#define AED_PROJ_2021_COMPANY_H

#include "Airport.h"
#include "Client.h"
#include "Flight.h"

#include <fstream>

class Company {
private:
    std::vector<Flight *> _flights{};
    std::vector<Plane *> _planes{};
    std::vector<Client *> _clients{};
    std::vector<Airport *> _airports{};

    /**
     * @brief Loads planes from file.
     */
    void readPlane();

    /**
     * @brief Loads clients from file.
     */
    void readClient();

    /**
     * @brief Writes planes to file.
     */
    void writePlane();

    /**
     * @brief Writes clients to file.
     */
    void writeClient();

public:
    /**
     * @brief Populates this company with data from files.
     */
    void populate();

    std::vector<Flight *> getFlights() const { return _flights; };

    std::vector<Plane *> getPlanes() const { return _planes; };

    std::vector<Client *> getClients() const { return _clients; };

    Client *createClient(unsigned nif, std::string name);

    void updateClient(Client *client, std::string name);

    void deleteClient(Client *client);

    Flight *createFlight(unsigned number, unsigned duration, Airport *origin,
                         Airport *dest, std::string departure, Plane *plane);

    void updateFlight(Flight *flight, std::string duration, std::string origin,
                      std::string dest, std::string departure,
                      std::string plane);

    void deleteFlight(Flight *flight);

    Plane *createPlane(unsigned rows, unsigned columns, std::string plate,
                       std::string type);

    void updatePlane(Plane *plane, std::string rows, std::string columns);

    void deletePlane(Plane *plane);

    Airport *createAirport(std::string name);

    void updateAirport(Airport *airport, std::string name);

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
