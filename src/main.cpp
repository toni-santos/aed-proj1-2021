#include <chrono>
#include <iostream>
#include <thread>

#include "../includes/Company.h"
#include "../includes/Exceptions.h"
#include "../includes/UserInterface.h"

int main() {
    UserInterface ui;

    try {
        Company comp = Company();

        while (true) {
            ui.show(comp);
        }
    } catch (Exit) {
        ui.exit();
    } catch (ReadError) {
        std::cout << "Something went wrong reading a file!" << std::endl;
    } catch (...) {
        std::cout << "Escreve direito burro" << std::endl;
    }
    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
