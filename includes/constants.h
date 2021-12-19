#ifndef AED_PROJ_2021_CONSTANTS_H
#define AED_PROJ_2021_CONSTANTS_H

#include <ostream>

// Files
const std::string CLIENT_FILE_PATH = "../../input/client.tsv";
const std::string PLANE_FILE_PATH = "../../input/plane.tsv";
const std::string AIRPORT_FILE_PATH = "../../input/airport.tsv";

// Terminal escape sequences
#ifdef NO_ANSI

const struct ClearScreen {
    friend std::ostream &operator<<(std::ostream &out, const ClearScreen &c) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        return out;
    }
} CLEAR_SCREEN;

// const std::string CLEAR_SCREEN = "\n\n";
const std::string ERROR_MESSAGE = "";
const std::string CONCEAL_TEXT = "";
const std::string STRIKE_THROUGH = "";
const std::string DISABLE_CURSOR = "";
const std::string ENABLE_CURSOR = "";
const std::string RESET_FORMATTING = "";
#else
const std::string CLEAR_SCREEN = "\33[2J\33[H";
const std::string ERROR_MESSAGE = "\33[31m";
const std::string CONCEAL_TEXT = "\33[8m";
const std::string STRIKE_THROUGH = "\33[9m";
const std::string DISABLE_CURSOR = "\33[?25l";
const std::string ENABLE_CURSOR = "\33[?25h";
const std::string RESET_FORMATTING = "\33[0m";
#endif

// Others
const std::string COMPANY_NAME =
    STRIKE_THROUGH + "[REDACTED]" + RESET_FORMATTING + " AIRLINES";

#endif // AED_PROJ_2021_CONSTANTS_H
