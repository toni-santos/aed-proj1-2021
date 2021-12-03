#include "../includes/Utils.h"

void readFile(std::string filePath) {
    std::ifstream i;

    i.open(filePath);
    if (i.good()){
        std::cout << i.rdbuf() << std::endl;
    }

    i.close();
}

std::vector<std::string> split(std::string str) {
    std::string temp;
    std::vector<std::string> final;

    for (auto i : str) {
        if (i == ' ') {
            final.push_back(temp);
            temp = "";
        } else {
            temp += i;
        }
    }
    final.push_back(temp);

    return final;
}