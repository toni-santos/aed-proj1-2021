#ifndef AED_PROJ_2021_UTILS_H
#define AED_PROJ_2021_UTILS_H

#include "Airport.h"
#include "BST.h"
#include "Client.h"
#include "Flight.h"
#include "Plane.h"
#include "Service.h"
#include "Transport.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

/**
 * @brief Splits a string by a character.
 *
 * @param str The string to be split.
 * @param i The character to use as the separator.
 * @return A vector with all the words in the string that were separated by the
 *         given character.
 */
std::vector<std::string> split(std::string str, char i);

/**
 * @brief Normalizes a string.
 *
 * @details Replaces all tabs with spaces, removes duplicate spaces and trims
 *          spaces from the start and the end.
 *
 * @param input The string to normalize.
 */
void normalizeInput(std::string &input);

/**
 * @brief Calculates the length of a number in base 10.
 *
 * @param n The number.
 * @return The length of the number.
 */
unsigned numberLength(unsigned n);

/**
 * @brief Sleeps for a certain amount of time.
 *
 * @param millis The time to sleep for, in milliseconds.
 */
void sleep(const unsigned millis);

/**
 * @brief Prints info about some planes to the screen.
 *
 * @param planes The planes.
 */
void printPlanes(const std::vector<Plane *> &planes);

/**
 * @brief Prints info about some flights to the screen.
 *
 * @param flights The flights.
 */
void printFlights(const std::vector<Flight *> &flights);

/**
 * @brief Prints info about the services of some planes to the screen.
 *
 * @param planes The planes.
 */
void printServices(const std::vector<Plane *> &planes);

/**
 * @brief Prints info about the services of a plane to the screen.
 *
 * @param planes The plane.
 */
void printServices(const Plane *plane);

/**
 * @brief Prints info about some clients to the screen.
 *
 * @param clients The clients.
 */
void printClients(const std::vector<Client *> &clients);

/**
 * @brief Prints info about some airports to the screen.
 *
 * @param airports The airports.
 */
void printAirports(const std::vector<Airport *> &airports);

/**
 * @brief Prints info about some luggage carts to the screen.
 *
 * @param flights The flights with which the carts are associated.
 */
void printCarts(const std::vector<Flight *> &flights);

/**
 * @brief Prints info about a transport to the screen.
 *
 * @param transport The transport.
 */
void printTransport(const Transport *t);

/**
 * @brief Prints info about some transports to the screen.
 *
 * @param transports The transports.
 * @param reverse Whether to print in reverse order.
 */
void printTransports(const BST<Transport> &transports, bool reverse = false);

/**
 * @brief Prints all the seats in a flight in a grid.
 *
 * @param flight The flight.
 */
void printPlaneLayout(const Flight *flight);

/**
 * @brief Prints info about some tickets to the screen.
 *
 * @param tickets The tickets.
 */
void printTickets(const std::vector<Ticket *> &tickets);

#endif // AED_PROJ_2021_UTILS_H
