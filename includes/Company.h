#ifndef AED_PROJ_2021_COMPANY_H
#define AED_PROJ_2021_COMPANY_H

#include "Client.h"
#include "Flight.h"

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

    /**
     * @brief Writes flights to file.
     */
    void writeFlight();

    /**
     * @brief Writes planes to file.
     */
    void writePlane();

    /**
     * @brief Writes services to file.
     */
    void writeService();

    /**
     * @brief Writes clients to file.
     */
    void writeClient();

public:
    /**
     * @brief Populates a flights "tickets" attribute and adds the flight to the
     * planes vector of flights
     *
     * @param plane The Plane object.
     *
     * @param client The Flight object.
     */
    void populateFlight(Plane plane, Flight flight);

    /**
     * @brief Adds a client to _clients.
     *
     * @param client The Client object to be added to _clients.
     */
    void addClient(Client client);

    void addPlane(Plane plane);

    /**
     * @brief Populates this company with data from files.
     */
    void populate();

    std::vector<Flight> getFlights() const { return _flights; };

    std::vector<Plane> getPlanes() const { return _planes; };

    std::vector<Client> getClients() const { return _clients; };

    /**
     * @brief Iterates over the _flights vector to find the flight with
     * flightID.
     *
     * @param flightID The ID of the flight that is being searched
     */
    Flight *findFlight(unsigned flightID);

    /**
     * @brief Iterates over the _clients vector to find the client with NIF.
     *
     * @param flightID The NIF of the client that is being searched
     */
    Client *findClient(unsigned NIF);

    void removeClient(int pos) {
        _clients.erase(_clients.begin() + pos);
    }

    void removePlane(int pos) {
        _planes.erase(_planes.begin() + pos);
    }

    void updateClientInfo(int pos, std::string name, std::string strNIF) {
        if (name != "") {
            _clients.at(pos).setName(name);
        }

        if (strNIF != "") {
            _clients.at(pos).setNIF(stoul(strNIF));
        }
    }

    void updatePlaneInfo(int pos, std::string plate, std::string type, std::string capacity, std::string id){
        if (plate != "") {
            _planes.at(pos).setPlate(plate);
        }

        if (type != "") {
            _planes.at(pos).setType(type);
        }

        if (capacity != "") {
            _planes.at(pos).setCapacity(stoul(capacity));
        }

        if (id != "") {
            _planes.at(pos).setId(stoul(id));
        }
    }


};

#endif // AED_PROJ_2021_COMPANY_H
