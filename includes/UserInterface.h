#ifndef AED_PROJ_2021_USER_INTERFACE_H
#define AED_PROJ_2021_USER_INTERFACE_H

#include "Company.h"

enum Menu {
    EXIT,
    MAIN,

    CLIENT,
    CLIENT_OPTIONS,
    CHECK_FLIGHTS,
    BUY_TICKETS,

    EMPLOYEE,
    EMPLOYEE_OPTIONS,
    PLANES,
    CREATE_PLANE,
    READ_PLANE,
    UPDATE_PLANE,
    DELETE_PLANE,
    FLIGHTS,
    CREATE_FLIGHT,
    READ_FLIGHT,
    UPDATE_FLIGHT,
    DELETE_FLIGHT,
    SERVICES,
    CREATE_SERVICE,
    READ_SERVICE,
    COMPLETE_SERVICE,
    CLIENTS,
    CREATE_CLIENT,
    READ_CLIENT,
    UPDATE_CLIENT,
    DELETE_CLIENT,
    AIRPORTS,
    CREATE_AIRPORT,
    DELETE_AIRPORT,
    READ_AIRPORT
};

class UserInterface {
    /**
     * @brief Specifies which menu to show.
     */
    Menu _currentMenu = MAIN;

    /**
     * @brief The error message to show.
     */
    std::string _errorMessage{};

    /**
     * @brief The current client that is accessing the platform
     */
    Client *currClient = nullptr;

    /**
     * @brief Helper method to show a menu with options.
     *
     * @details Each option string will be shown along with its index on the
     *          list. When the user inputs one of the indices of the list
     *          _currentMenu will be set to that option's Menu.
     *
     * @note The first option on the list will be shown last and is
     *       intended to be a way to go back in the navigation tree.
     *
     * @note This can show an arbitrary amount of options, but only navigate to
     *       the first 10 options.
     *
     * @param text Text to show before the options
     * @param options The list of options to show
     */
    void optionsMenu(const std::string &text,
                     const std::vector<std::pair<std::string, Menu>> &options);

    void loadString(const std::string &text, unsigned time) const;

    unsigned getNumberInput(std::string prompt, unsigned min = 0,
                            unsigned max = INT32_MAX);

    bool inRange(unsigned n, unsigned min, unsigned max);

    /**
     * @brief Shows the main menu.
     */
    void mainMenu();

    /**
     * @brief Shows the client menu.
     */
    void clientMenu(Company &comp);
    /**
     * @brief Shows the client options menu.
     */
    void clientOptionsMenu();

    /**
     * @brief Shows the employee menu.
     */
    void employeeMenu();

    /**
     * @brief Shows the employee options menu.
     */
    void employeeOptionsMenu();

    /**
     * @brief Shows the employee CRUD operations over clients.
     * @param comp the company
     */
    void clientsMenu(Company &comp);

    /**
     * @brief Shows the client the flights they have booked.
     * @param comp the company
     */
    void clientsFlightsMenu(Company &comp);

    /**
     * @brief Shows the employee a menu to create a new client.
     * @param comp the company
     */
    void createClientMenu(Company &comp);

    /**
     * @brief Shows the employee a menu to see a specific's client information
     * (can be ordered by several parameters).
     * @param comp the company
     */
    void readClientMenu(Company &comp);

    /**
     * @brief Shows the employee a menu to delete a client.
     * @param comp the company
     */
    void deleteClientMenu(Company &comp);

    /**
     * @brief Shows the employee a menu to alter a specific's client
     * information.
     * @param comp the company
     */
    void updateClientMenu(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over the services.
     * @param comp the company
     */
    void servicesMenu(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over the planes.
     * @param comp the company
     */
    void planesMenu(Company &comp);

    /**
     * @brief Shows the employee a menu to see a specific's plane information
     * (can be ordered by several parameters).
     * @param comp the company
     */
    void checkPlane(Company &comp);

    /**
     * @brief Shows the employee a menu to create a new plane.
     * @param comp the company
     */
    void createPlane(Company &comp);

    /**
     * @brief Shows the employee a menu to alter a specific's plane information.
     * @param comp the company
     */
    void updatePlane(Company &comp);

    /**
     * @brief Shows the employee a menu to delete a plane.
     * @param comp the company
     */
    void deletePlane(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over the flights.
     * @param comp the company
     */
    void flightsMenu(Company &comp);

    /**
     * @brief Shows the employee a menu to create a new service.
     * @param comp the company
     */
    void createService(Company &comp);

    void readService(Company &comp);

    void createFlight(Company &comp);

    void readFlight(Company &comp);

    void updateFlight(Company &comp);

    void removeFlight(Company &comp);

    void clientBuyTickets(Company &comp);

    void completeService(Company &comp);

    void airportsMenu(Company &comp);

    void createAirport(Company &comp);

    void deleteAirport(Company &comp);

    void readAirport(Company &comp);

public:
    /**
     * @brief Shows the current menu.
     *
     * @param comp
     */
    void show(Company &comp);
    /**
     * @brief Shows a message before the program exits.
     */
    void exit();
};

/**
 * @brief Prints each attribute of the plane in the order of the sortedVec
 *
 * @param sortedVec Vector sorted according to previous user decision
 */
void printPlaneVector(std::vector<Plane> sortedVec);

/**
 * @brief Prints all of the flights' information of a given client
 *
 * @param client The client that is getting their flights printed
 * @param comp The company
 */
void printClientFlights(Client *client, Company &comp);

/**
 * @brief Prints each attribute of the client in the order of the sortedVec
 *
 * @param sortedVec vector sorted according to previous user decision
 * @param comp the company
 */
void printClientVector(std::vector<Client> sortedVec, Company &comp);

void printFlightVector(std::vector<Flight *> sortedVec);

void printAirportVector(Company &comp);

void printServiceList(Company &comp);

void printPlaneServices(Plane *plane);

#endif // AED_PROJ_2021_MENU_H
