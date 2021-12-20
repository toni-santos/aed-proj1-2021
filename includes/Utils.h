#ifndef AED_PROJ_2021_UTILS_H
#define AED_PROJ_2021_UTILS_H

#include <iostream>
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

#endif // AED_PROJ_2021_UTILS_H
