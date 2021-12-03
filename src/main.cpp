#include <iostream>

#include "../includes/Menu.h"
#include "../includes/Company.h"

int main() {
    try {
        Company comp = Company();
        Menu menu;
        menu.menu(comp);
    } catch (...) {
        std::cout << "Escreve direito burro" << std::endl;
    }
    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
