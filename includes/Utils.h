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

// TODO: Documentation
void sleep(const unsigned millis);

/**
 * @brief Prints each attribute of the plane in the order of the sortedVec
 *
 * @param planes Vector sorted according to previous user decision
 */
void printPlanes(const std::vector<Plane *> &planes);

/**
 * @brief Prints each attribute of the flight in the order of the sortedVec
 *
 * @param sortedVec Vector sorted according to previous user decision
 */
void printFlights(const std::vector<Flight *> &flights);

/**
 * @brief Applies a function to all planes that displays their pending and done
 * services.
 *
 * @param comp The company
 */
void printServices(const std::vector<Plane *> &planes);

void printServices(const Plane *plane);

/**
 * @brief Prints each attribute of the client in the order of the sortedVec
 *
 * @param sortedVec Vector sorted according to previous user decision
 * @param comp The company
 */
void printClients(const std::vector<Client *> &clients);

/**
 * @brief Prints each attribute of all airports.
 *
 * @param comp The company
 */
void printAirports(const std::vector<Airport *> &airports);

void printCarts(const std::vector<Cart *> &carts);

void printTransport(const Transport *t);

void printTransports(const BST<Transport> &transports, bool reverse = false);

void printPlaneLayout(const Flight *flight);

void printTickets(const std::vector<Ticket *> &tickets);

#endif // AED_PROJ_2021_UTILS_H
