#include "../includes/Utils.h"
#include "../includes/Exceptions.h"
#include "../includes/constants.h"

#include <chrono>
#include <cmath>
#include <thread>

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

unsigned numberLength(unsigned n) {
    unsigned nd = 0;

    do {
        ++nd;
        n /= 10;
    } while (n);

    return nd;
}

void sleep(const unsigned millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void printPlanes(const std::vector<Plane *> &planes) {
    std::cout << "ID - Type - Plate - Capacity - Services done - Services to "
                 "do - Flight IDs"
              << std::endl;

    for (const Plane *plane : planes) {
        std::cout << plane->getID() << " - " << plane->getType() << " - "
                  << plane->getPlate() << " - " << plane->getCapacity() << " - "
                  << plane->getServicesDone().size() << " - "
                  << plane->getServices().size() << " -";

        auto flights{plane->getFlights()};

        if (flights.empty())
            std::cout << " No flights";
        else
            for (const Flight *flight : flights)
                std::cout << ' ' << flight->getID();

        std::cout << '\n';
    }
}

void printFlights(const std::vector<Flight *> &flights) {
    std::cout << "Flight Number - Origin - Destination - Departure Date - "
                 "Duration - Availability - Plane ID"
              << std::endl;

    for (Flight *flight : flights) {
        std::cout << flight->getNumber() << " - "
                  << flight->getOrigin()->getName() << " - "
                  << flight->getDestination()->getName() << " - "
                  << flight->getDepartureDate() << " - "
                  << flight->getDuration() << " - " << flight->getAvailability()
                  << " - " << flight->getPlane()->getID() << std::endl;
    }
}

void printServices(const std::vector<Plane *> &planes) {
    for (auto plane : planes) {
        std::cout << "Type - Date - Worker\n\n";
        printServices(plane);
    }
}

void printServices(const Plane *plane) {
    std::cout << "Plane " << plane->getID() << std::endl;

    if (plane->getServices().size() == 0) {
        std::cout << "No services to be done!\n";
    } else {
        std::cout << "To do:\n";

        for (const Service &service : plane->getServices())
            std::cout << service.getTypeStr() << " - " << service.getWorker()
                      << " - " << service.getDate() << '\n';
    }
    std::cout << std::endl;

    if (plane->getServicesDone().size() == 0) {
        std::cout << "No services have been done!\n";
    } else {
        std::cout << "Done:\n";

        for (const Service &service : plane->getServicesDone())
            std::cout << service.getTypeStr() << " - " << service.getWorker()
                      << " - " << service.getDate() << '\n'
                      << std::flush;
    }
    std::cout << std::endl;
}

void printClients(const std::vector<Client *> &clients) {
    std::cout << "NIF - Name - Tickets\n";

    for (const Client *client : clients)
        std::cout << client->getNIF() << " - " << client->getName() << " - "
                  << client->getTickets().size() << " tickets" << std::endl;
}

void printAirports(const std::vector<Airport *> &airports) {
    std::cout << "ID - Name - Transports\n";

    for (Airport *a : airports)
        std::cout << a->getID() << " - " << a->getName() << " - "
                  << a->getTransports().size() << " transports" << std::endl;
}

void printCarts(const std::vector<Cart *> &carts) {
    std::cout << "Flight ID - Cart Size - Trolley Size - Stack Size\n"
              << std::flush;

    for (const Cart *cart : carts)
        std::cout << cart->getFlight()->getID() << " - " << cart->getCartSize()
                  << " - " << cart->getTrolleySize() << " - "
                  << cart->getStackSize() << std::endl;
}

void printTransport(Transport t) {
    std::cout << t.getName() << " - " << t.getTypeStr() << " - ";
    auto timetable{t.getTimetable()};
    for (auto i{timetable.begin()}, end{timetable.end()}; i != end; ++i) {
        std::cout << i->getElement() << ' ' << std::flush;
    }
    std::cout << std::endl;
}

void printTransports(const BST<Transport> &transports, bool reverse) {
    if (reverse)
        for (auto i{transports.rbegin()}, end{transports.rend()}; i != end; ++i)
            printTransport(i->getElement());
    else
        for (auto t{transports.begin()}, end{transports.end()}; t != end; ++t)
            printTransport(t->getElement());
}

void printPlaneLayout(const Flight *flight) {
    Plane *plane = flight->getPlane();
    unsigned rows = plane->getRows();
    unsigned columns = plane->getColumns();
    unsigned width = numberLength(columns);

    for (int j = width - 1; j >= 0; j--) {
        std::cout << "  ";
        for (unsigned i = 1; i <= columns; i++) {
            std::cout << i / ((unsigned)pow(10, j)) % 10;
        }
        std::cout << '\n';
    }

    for (unsigned row = 0; row < rows; ++row) {
        printf("%c ", 'A' + row);
        for (unsigned column = 0; column < columns; ++column) {
            Ticket *ticket = flight->getTickets().at(row * columns + column);

            std::cout << (ticket->getClient()
                              ? RED_TEXT + "x" + RESET_FORMATTING
                              : GREEN_TEXT + "o" + RESET_FORMATTING);
        }

        std::cout << std::endl;
    }
}

void printTickets(const std::vector<Ticket *> &tickets) {
    std::cout << "Flight Number - Origin - Destination - Date of Departure - "
                 "Seat\n";

    for (auto ticket : tickets) {
        const Flight *f = ticket->getFlight();

        std::cout << f->getNumber() << " - " << f->getOrigin()->getName()
                  << " - " << f->getDestination()->getName() << " - "
                  << f->getDepartureDate() << " - " << ticket->getSeat()
                  << std::endl;
    }
}
