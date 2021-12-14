#include <chrono>
#include <iostream>
#include <thread>

#include "../includes/Company.h"
#include "../includes/Exceptions.h"
#include "../includes/UserInterface.h"

int main() {
    UserInterface ui;
    Company comp;

    try {
        comp.populate();
    } catch (ReadError) {
        std::cerr << "Something went wrong reading a file!" << std::endl;
        return 1;
    }

    try {
        while (true) {
            ui.show(comp);
        }
    } catch (Exit) {
        ui.exit();
    }
    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
