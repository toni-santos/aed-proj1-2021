#ifndef AED_PROJ_2021_UTILS_H
#define AED_PROJ_2021_UTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void readFile(std::string filePath);
std::vector<std::string> split(std::string str, char i);
void normalizeInput(std::string &input);
bool getInput(std::string &input);

#endif // AED_PROJ_2021_UTILS_H
