#ifndef AED_PROJ_2021_COMPANY_H
#define AED_PROJ_2021_COMPANY_H

#include "Client.h"
#include "Flight.h"

#include "fstream"

class Company {
private:
    std::vector<Flight> _flights;
    std::vector<Plane> _planes;
    std::vector<Client> _clients;

    /**
     * @brief Loads flights from file.
     */
    void readFlight();

    /**
     * @brief Loads planes from file.
     */
    void readPlane();

    /**
     * @brief Loads services from file.
     */
    void readService();

    /**
     * @brief Loads clients from file.
     */
    void readClient();

public:
    void addPlane(Plane plane, Flight flight);

    /**
     * @brief Populates this company with data from files.
     */
    void populate();

    std::vector<Flight> getFlights() const { return _flights; };

    std::vector<Plane> getPlanes() const { return _planes; };

    std::vector<Client> getClients() const { return _clients; };
};

#endif // AED_PROJ_2021_COMPANY_H
