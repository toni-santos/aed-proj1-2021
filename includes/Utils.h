#ifndef AED_PROJ_2021_UTILS_H
#define AED_PROJ_2021_UTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Reads a certain file.
 *
 * @param filePath
 */
void readFile(std::string filePath);

/**
 * @brief Creates a vector of all the words in str separated by a character i.
 *
 * @param str The string to be split.
 * @param i The character that serves as separation.
 * @return A vector of all the words in str that were separated by the character
 * i.
 */
std::vector<std::string> split(std::string str, char i);

/**
 * @brief Normalizes input.
 *
 * Replaces all tabs with spaces, removes duplicate spaces and trims spaces from
 * the start and the end.
 *
 * @param input The input to normalize
 */
void normalizeInput(std::string &input);

/**
 *
 * @param n The number to be analyzed.
 * @return An unsigned integer equal to the number of digits of a given number
 * n.
 */
unsigned numberLength(unsigned n);

#endif // AED_PROJ_2021_UTILS_H
