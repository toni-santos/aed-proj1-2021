#include "../includes/Utils.h"
#include "../includes/Exceptions.h"

void readFile(std::string filePath) {
    std::ifstream i;

    i.open(filePath);
    if (i.good()) {
        std::cout << i.rdbuf() << std::endl;
    }

    i.close();
}

std::vector<std::string> split(std::string str, char sep) {
    std::string temp;
    std::vector<std::string> final;

    for (auto i : str) {
        if (i == sep) {
            final.push_back(temp);
            temp = "";
        } else {
            temp += i;
        }
    }
    final.push_back(temp);

    return final;
}

void getInput(std::string &input) {
    std::getline(std::cin, input);
    normalizeInput(input);

    if (std::cin.eof())
        throw Exit();
}

void normalizeInput(std::string &input) {
    char last = 0;
    size_t i = 0;
    while (i < input.length()) {
        char &c = input.at(i);

        // Replace tabs with spaces
        if (c == '\t')
            c = ' ';

        // Delete character if it is a space at the begining, at the end or
        // after another space
        if (c == ' ' &&
            (last == ' ' || last == 0 || i == input.length() - 1 || i == 0)) {
            input.erase(i, 1);

            // If we're outside the string, go back one
            if (i == input.length())
                i--;
        } else {
            i++;
            last = c;
        }
    }
}