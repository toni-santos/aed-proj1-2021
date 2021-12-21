#ifndef AED_PROJ_2021_USER_INTERFACE_H
#define AED_PROJ_2021_USER_INTERFACE_H

#include "Company.h"

/**
 * @brief Holds the possible menu values.
 */
enum Menu {
    /**
     * @brief Exits the program.
     */
    EXIT,
    /**
     * @brief Shows the main options.
     */
    MAIN,

    /**
     * @brief Authenticates a client.
     */
    C_AUTH,
    /**
     * @brief Shows the options for a client.
     */
    C_OPTIONS,
    /**
     * @brief Shows all flights to a client.
     */
    C_CHECK_FLIGHTS,
    /**
     * @brief Lets a client buy tickets.
     */
    C_BUY_TICKETS,
    /**
     * @brief Shows all transports near an airport to a client.
     */
    C_CHECK_TRANSPORTS,

    /**
     * @brief Authenticates an employee.
     */
    E_AUTH,
    /**
     * @brief Shows the options for an employee.
     */
    E_OPTIONS,

    /**
     * @brief Shows the plane options.
     */
    E_PLANE_OPTIONS,
    /**
     * @brief Creates a new plane.
     */
    E_PLANE_CREATE,
    /**
     * @brief Shows all planes.
     */
    E_PLANE_READ,
    /**
     * @brief Updates a plane.
     */
    E_PLANE_UPDATE,
    /**
     * @brief Deletes a plane.
     */
    E_PLANE_DELETE,

    /**
     * @brief Shows the flight options.
     */
    E_FLIGHT_OPTIONS,
    /**
     * @brief Creates a new flight.
     */
    E_FLIGHT_CREATE,
    /**
     * @brief Shows all flights.
     */
    E_FLIGHT_READ,
    /**
     * @brief Updates a flight.
     */
    E_FLIGHT_UPDATE,
    /**
     * @brief Deletes a flight.
     */
    E_FLIGHT_DELETE,

    /**
     * @brief Shows the service options.
     */
    E_SERVICE_OPTIONS,
    /**
     * @brief Creates a new service.
     */
    E_SERVICE_CREATE,
    /**
     * @brief Shows all services.
     */
    E_SERVICE_READ,
    /**
     * @brief Deletes a service.
     */
    E_SERVICE_COMPLETE,

    /**
     * @brief Shows the client options.
     */
    E_CLIENT_OPTIONS,
    /**
     * @brief Creates a new client.
     */
    E_CLIENT_CREATE,
    /**
     * @brief Shows all clients.
     */
    E_CLIENT_READ,
    /**
     * @brief Updates a client.
     */
    E_CLIENT_UPDATE,
    /**
     * @brief Deletes a client.
     */
    E_CLIENT_DELETE,

    /**
     * @brief Shows the airport options.
     */
    E_AIRPORT_OPTIONS,
    /**
     * @brief Creates a new airport.
     */
    E_AIRPORT_CREATE,
    /**
     * @brief Shows all airports.
     */
    E_AIRPORT_READ,
    /**
     * @brief Deletes an airport.
     */
    E_AIRPORT_DELETE,

    /**
     * @brief Shows the cart options.
     */
    E_CART_OPTIONS,
    /**
     * @brief Shows all carts.
     */
    E_CART_READ,
    /**
     * @brief Updates a cart.
     */
    E_CART_UPDATE,

    /**
     * @brief Shows the transport options.
     */
    E_TRANSPORT_OPTIONS,
    /**
     * @brief Creates a new transport.
     */
    E_TRANSPORT_CREATE,
    /**
     * @brief Shows all transports.
     */
    E_TRANSPORT_READ,
    /**
     * @brief Updates a transport.
     */
    E_TRANSPORT_UPDATE,
    /**
     * @brief Deletes a transport.
     */
    E_TRANSPORT_DELETE
};

/**
 * @brief Implements the terminal interface for the user to interact with the
 *        company.
 */
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
    Client *_currentClient = nullptr;

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
     * @param text Text to show before the options
     * @param options The list of options to show
     */
    void optionsMenu(const std::string &text,
                     const std::vector<std::pair<std::string, Menu>> &options);

    /**
     * @brief Procedurally displays a string in the console (as if it were an
     * airplane's trail)
     *
     * @param text The text to be displayed.
     * @param time The time (in milliseconds) it takes to display the text.
     */
    void loadString(const std::string &text, unsigned time) const;

    /**
     * @brief Gets a line from stdin and normalizes it.
     *
     * @note Also shows _errorMessage and then resets it.
     *
     * @throws Exit if the EOF bit is set.
     *
     * @param prompt Shown to the user.
     * @return The user input.
     */
    std::string getInput(std::string prompt);

    /**
     * @brief Tries to transform a string into an unsigned integer, displaying
     * an error message if it fails.
     *
     * @note There are optional parameters (min and max) to also display an
     * error message if the prompt is outside of the designated limit.
     *
     * @note Also shows _errorMessage and then resets it.
     *
     * @param prompt Shown to the user.
     * @param min The left bound of the limit (inclusive).
     * @param max The right bound of the limit (inclusive).
     * @return The user input, as an unsigned integer.
     */
    unsigned getNumberInput(std::string prompt, long min = 0,
                            long max = INT32_MAX);

    /**
     * @brief Checks if an unsigned integer n is inside the limit [min, max].
     *
     * @param n The number to be checked.
     * @param min The left bound of the limit.
     * @param max The right bound of the limit.
     * @return A boolean that confirms whether or not min <= n <= max.
     */
    bool inRange(long n, long min, long max);

    Client *getOrCreateClient(Company &comp, unsigned nif);

    /**
     * @brief Shows the main menu.
     */
    void mainMenu();

    /**
     * @brief Shows the client menu.
     */
    void clientAuthMenu(Company &comp);
    /**
     * @brief Shows the client options menu.
     */
    void clientOptionsMenu();
    /**
     * @brief Shows the client the flights they have booked.
     *
     * @param comp the company
     */
    void cCheckFlightsMenu(Company &comp);
    /**
     * @brief Shows the client a menu to purchase a ticket to a flight.
     *
     * @note Can be purchased individually or in multiple quantities (in group,
     * one for each client), and checks if the client wants to use the automatic
     * luggage system.
     *
     * @param comp the company
     */
    void cBuyTicketsMenu(Company &comp);
    /**
     * @brief Shows transports near an airport to the client.
     *
     * @param comp the company
     */
    void cCheckTransportsMenu(Company &comp);

    /**
     * @brief Shows the employee menu.
     */
    void employeeAuthMenu();
    /**
     * @brief Shows the employee options menu.
     */
    void employeeOptionsMenu();

    /**
     * @brief Shows the employee CRUD operations over the planes.
     */
    void ePlaneOptionsMenu();
    /**
     * @brief Shows the employee a menu to create a new plane.
     * @param comp the company
     */
    void ePlaneCreateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to see a specific's plane information
     * (can be ordered by several parameters).
     * @param comp the company
     */
    void ePlaneReadMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to alter a specific plane's information.
     * @param comp the company
     */
    void ePlaneUpdateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to delete a plane.
     * @param comp the company
     */
    void ePlaneDeleteMenu(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over the flights.
     */
    void eFlightOptionsMenu();
    /**
     * @brief Shows the employee a menu to create a new flight.
     * @param comp the company
     */
    void eFlightCreateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to see all of the flights' information
     * (can be ordered by several parameters).
     * @param comp the company
     */
    void eFlightReadMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to alter a specific flight's
     * information.
     * @param comp the company
     */
    void eFlightUpdateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to remove a flight.
     * @param comp the company
     */
    void eFlightDeleteMenu(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over the services.
     */
    void eServiceOptionsMenu();
    /**
     * @brief Shows the employee a menu to create a new service.
     * @param comp the company
     */
    void eServiceCreateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu that displays all of the company comp's
     * services.
     * @param comp the company
     */
    void eServiceReadMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to complete a pending service.
     * @param comp the company
     */
    void eServiceCompleteMenu(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over clients.
     */
    void eClientOptionsMenu();
    /**
     * @brief Shows the employee a menu to create a new client.
     * @param comp the company
     */
    void eClientCreateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to see a specific client's information
     * (can be ordered by several parameters).
     * @param comp the company
     */
    void eClientReadMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to alter a specific client's
     * information.
     * @param comp the company
     */
    void eClientUpdateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to delete a client.
     * @param comp the company
     */
    void eClientDeleteMenu(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over the airports.
     */
    void eAirportOptionsMenu();
    /**
     * @brief Shows the employee a menu to create a new airport.
     * @param comp the company
     */
    void eAirportCreateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu of all existing airports.
     * @param comp the company
     */
    void eAirportReadMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to delete an airport.
     * @param comp the company
     */
    void eAirportDeleteMenu(Company &comp);

    void eCartOptionsMenu();
    /**
     * @brief Shows the employee a menu to see a specific cart's
     * information.
     * @param comp the company
     */
    void eCartReadMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to alter a specific cart's
     * information.
     * @param comp the company
     */
    void eCartUpdateMenu(Company &comp);

    /**
     * @brief Shows the employee CRUD operations over transports.
     */
    void eTransportOptionsMenu();
    /**
     * @brief Shows the employee a menu to create a new transport.
     * @param comp the company
     */
    void eTransportCreateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to see a specific transport's
     * information.
     * @param comp the company
     */
    void eTransportReadMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to alter a specific transport's
     * information.
     * @param comp the company
     */
    void eTransportUpdateMenu(Company &comp);
    /**
     * @brief Shows the employee a menu to delete a transport.
     * @param comp the company
     */
    void eTransportDeleteMenu(Company &comp);

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

#endif // AED_PROJ_2021_MENU_H
