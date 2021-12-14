#include <chrono>
#include <iostream>
#include <thread>

#include "../includes/Company.h"
#include "../includes/Exceptions.h"
#include "../includes/Menu.h"

int main() {
    Menu menu;

    try {
        Company comp = Company();

        while (true) {
            menu.menu(comp);
        }
    } catch (Exit) {
        menu.exit();
    } catch (ReadError) {
        std::cout << "Something went wrong reading a file!" << std::endl;
    } catch (...) {
        std::cout << "Escreve direito burro" << std::endl;
    }
    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
