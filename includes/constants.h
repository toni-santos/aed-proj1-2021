#ifndef AED_PROJ_2021_CONSTANTS_H
#define AED_PROJ_2021_CONSTANTS_H

// Files
const std::string CLIENT_FILE_PATH = "../input/client.tsv";
const std::string PLANE_FILE_PATH = "../input/plane.tsv";
const std::string AIRPORT_FILE_PATH = "../input/airport.tsv";

// Terminal escape sequences
const std::string CLEAR_SCREEN = "\e[2J\e[H";
const std::string ERROR_MESSAGE = "\e[31m";
const std::string CONCEAL_TEXT = "\e[8m";
const std::string STRIKE_THROUGH = "\e[9m";
const std::string DISABLE_CURSOR = "\e[?25l";
const std::string ENABLE_CURSOR = "\e[?25h";
const std::string RESET_FORMATTING = "\e[0m";

// Others
// hi :D
// nada disto funfa no clion :(
const std::string COMPANY_NAME =
    STRIKE_THROUGH + "[REDACTED]" + RESET_FORMATTING + " AIRLINES";

#endif // AED_PROJ_2021_CONSTANTS_H
