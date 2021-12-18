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
    READ_AIRPORT,
	CARTS,
	READ_CART,
	UPDATE_CART
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

    /**
     * @brief Procedurally displays a string in the console (as if it were an airplane's trail)
     *
     * @param text The text to be displayed.
     * @param time The time (in milliseconds) it takes to display the text.
     */
    void loadString(const std::string &text, unsigned time) const;

    /**
     * @brief Tries to transform a string into an unsigned integer, displaying an error message if it fails.
     *
     * @note There are optional parameters (min and max) to also display an error message if the prompt is outside of
     * the designated limit.
     *
     * @param prompt The string to transform.
     * @param min The left bound of the limit.
     * @param max The right bound of the limit.
     * @return The unsigned integer version of the prompt.
     */
    unsigned getNumberInput(std::string prompt, unsigned min = 0,
                            unsigned max = INT32_MAX);

    /**
     * @brief Checks if an unsigned integer n is inside the limit [min, max].
     *
     * @param n The number to be checked.
     * @param min The left bound of the limit.
     * @param max The right bound of the limit.
     * @return A boolean that confirms whether or not min <= n <= max.
     */
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
     * @brief Shows the employee a menu to see a specific client's information
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
     * @brief Shows the employee a menu to alter a specific client's
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
     * @brief Shows the employee a menu to alter a specific plane's information.
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
    /**
     * @brief Shows the employee a menu that displays all of the company comp's services.
     * @param comp the company
     */
    void readService(Company &comp);
    /**
     * @brief Shows the employee a menu to create a new flight.
     * @param comp the company
     */
    void createFlight(Company &comp);

    /**
     * @brief Shows the employee a menu to see all of the flights' information
     * (can be ordered by several parameters).
     * @param comp the company
     */
    void readFlight(Company &comp);

    /**
     * @brief Shows the employee a menu to alter a specific flight's information.
     * @param comp the company
     */
    void updateFlight(Company &comp);

    /**
     * @brief Shows the employee a menu to remove a flight.
     * @param comp the company
     */
    void removeFlight(Company &comp);

    /**
     * @brief Shows the client a menu to purchase a ticket to a flight.
     *
     * @note Can be purchased individually or in multiple quantities (in group, one for each client), and checks if the
     * client wants to use the automatic luggage system.
     *
     * @param comp the company
     */
    void clientBuyTickets(Company &comp);

    /**
     * @brief Shows the employee a menu to complete a pending service.
     * @param comp the company
     */
    void completeService(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over the airports.
     * @param comp the company
     */

    void airportsMenu(Company &comp);

    /**
     * @brief Shows the employee a menu to create a new airport.
     * @param comp the company
     */
    void createAirport(Company &comp);

    /**
     * @brief Shows the employee a menu to delete an airport.
     * @param comp the company
     */
    void deleteAirport(Company &comp);

    /**
     * @brief Shows the employee a menu of all existing airports.
     * @param comp the company
     */
    void readAirport(Company &comp);

    /**
    * @brief Processes the client's luggage and displays a confirmation message.
     *
     * @note Processing implies the addition of the luggage to the card and linking it to its owner (the client that
     * just bought the ticket).
    * @param comp the company
    */
    void doLuggaging(Company &comp, Flight *flight, unsigned NIF, std::string seat);

	void cartsMenu(Company &comp);

	void updateCart(Company &comp);

	void readCart(Company &comp);

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
 * @param sortedVec Vector sorted according to previous user decision
 * @param comp The company
 */
void printClientVector(std::vector<Client> sortedVec, Company &comp);

/**
 * @brief Prints each attribute of the flight in the order of the sortedVec
 *
 * @param sortedVec Vector sorted according to previous user decision
 */
void printFlightVector(std::vector<Flight *> sortedVec);

/**
 * @brief Prints each attribute of all airports.
 *
 * @param comp The company
 */
void printAirportVector(Company &comp);

/**
 * @brief Applies a function to all planes that displays their pending and done services.
 *
 * @param comp The company
 */
void printServiceList(Company &comp);

/**
 * @brief Displays the pending and done services of a specific plane.
 *
 * @param comp The company
 */
void printPlaneServices(Plane *plane);

void printCartVector(Company &comp);

#endif // AED_PROJ_2021_MENU_H
