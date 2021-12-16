#ifndef AED_PROJ_2021_UTILS_H
#define AED_PROJ_2021_UTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void readFile(std::string filePath);
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
 * @brief Gets a line from stdin and normalizes it.
 *
 * @param input Where to store the input
 *
 * @throws Exit if the EOF bit is set.
 */
void getInput(std::string &input);

unsigned numberLength(unsigned n);

#endif // AED_PROJ_2021_UTILS_H
