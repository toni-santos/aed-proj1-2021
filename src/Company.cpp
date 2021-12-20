#include "../includes/Company.h"
#include "../includes/Exceptions.h"
#include "../includes/Plane.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"

void Company::readPlane() {
    std::ifstream f{PLANE_FILE_PATH};

    if (f.fail())
        throw ReadError();

    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);

        if (line == "")
            break;

        parsedLine = split(line, '\t');

        unsigned rows = stoul(parsedLine.at(0));
        unsigned columns = stoul(parsedLine.at(1));
        std::string plate = parsedLine.at(2);
        std::string type = parsedLine.at(3);

        Plane *plane = createPlane(rows, columns, plate, type);

        // READ FLIGHTS
        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');
            auto i{parsedLine.begin()};

            unsigned number = stoul(*i++);
            unsigned duration = stoul(*i++);
            unsigned originIndex = stoul(*i++);
            unsigned destIndex = stoul(*i++);
            std::string date = *i++;

            Flight *flight =
                createFlight(number, duration, _airports.at(originIndex),
                             _airports.at(destIndex), date, plane);

            getline(f, line);
            parsedLine = split(line, '\t');
            if (line != "")
                for (auto s : parsedLine)
                    flight->addLuggage(
                        new Luggage(flight->findTicketBySeat(s)));

            getline(f, line);
            parsedLine = split(line, '\t');
            Cart *cart = findCart(flight);
            if (line != "")
                for (auto s : parsedLine)
                    cart->addLuggage(new Luggage(flight->findTicketBySeat(s)));
        }

        // READ DONE SERVICES
        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');

            ServiceType type =
                static_cast<ServiceType>(stoul(parsedLine.at(0)));
            std::string date = parsedLine.at(1);
            std::string worker = parsedLine.at(2);

            plane->addService({type, date, worker});
            plane->doService();
        }

        // READ SERVICES
        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');

            ServiceType type =
                static_cast<ServiceType>(stoul(parsedLine.at(0)));
            std::string date = parsedLine.at(1);
            std::string worker = parsedLine.at(2);

            plane->addService({type, date, worker});
        }
    }
    f.close();
}
void Company::readAirport() {
    std::ifstream f{AIRPORT_FILE_PATH};

    if (f.fail())
        throw ReadError();

    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);

        if (line == "")
            break;

        Airport *airport = createAirport(line);

        // READ TRANSPORTS
        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');

            auto i{parsedLine.begin()};

            unsigned t = stoul(*i++);
            TransportType type = static_cast<TransportType>(t);
            unsigned distance = stoul(*i++);
            std::string name = *i++;

            Transport transport{type, distance, name};

            for (auto end{parsedLine.end()}; i < end; ++i)
                transport.insertTime(*i);

            airport->addTransport(transport);
        }
    }
    f.close();
}
void Company::readClient() {
    std::ifstream f{CLIENT_FILE_PATH};

    if (f.fail())
        throw ReadError();

    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        std::getline(f, line);

        if (line == "")
            break;

        parsedLine = split(line, '\t');

        unsigned nif = stoul(parsedLine.at(0));
        std::string name = parsedLine.at(1);

        Client *client = createClient(nif, name);

        while (!f.eof()) {
            getline(f, line);

            if (line == "")
                break;

            parsedLine = split(line, '\t');

            unsigned flightID = stoul(parsedLine.at(0));
            std::string seat = parsedLine.at(1);

            Ticket *ticket = _flights.at(flightID)->findTicketBySeat(seat);
            ticket->setClient(client);
            client->addTicket(ticket);
        }
    }

    f.close();
}

void Company::writePlane() {
    // std::ofstream of{PLANE_FILE_PATH};
    std::ofstream of{"../../output/plane.tsv", std::ofstream::trunc};

    if (of.fail())
        throw WriteError();

    for (Plane *plane : _planes) {
        of << plane->getRows() << '\t' << plane->getColumns() << '\t'
           << plane->getPlate() << '\t' << plane->getType() << '\n';

        for (Flight *flight : plane->getFlights()) {
            of << flight->getNumber() << '\t' << flight->getDuration() << '\t'
               << flight->getOrigin()->getID() << '\t'
               << flight->getDestination()->getID() << '\t'
               << flight->getDepartureDate() << '\n';

            bool first = true;
            for (auto l : flight->getStorage()) {
                if (!first)
                    of << '\t';
                of << l->getTicket()->getSeat();
                first = false;
            }
            of << '\n';
            first = true;
            auto cart = findCart(flight)->getCart();
            for (auto trolley : cart) {
                for (auto stack : trolley) {
                    std::stack<Luggage *> temp{};

                    while (!stack.empty()) {
                        temp.push(stack.top());
                        stack.pop();
                    }

                    while (!temp.empty()) {
                        if (!first)
                            of << '\t';
                        of << temp.top()->getTicket()->getSeat();
                        temp.pop();
                        first = false;
                    }
                }
            }
            of << '\n';
        }
        of << '\n';

        for (const Service &service : plane->getServicesDone())
            of << service.getType() << '\t' << service.getDate() << '\t'
               << service.getWorker() << '\n';
        of << '\n';

        for (const Service &service : plane->getServices())
            of << service.getType() << '\t' << service.getDate() << '\t'
               << service.getWorker() << '\n';
        of << '\n';
    }
}
void Company::writeAirport() {
    // std::ofstream of{AIRPORT_FILE_PATH};
    std::ofstream of{"../../output/airport.tsv"};

    if (of.fail())
        throw WriteError();

    for (Airport *airport : _airports) {
        of << airport->getName() << '\n';

        auto transports = airport->getTransports();
        for (auto i{transports.bylevelBegin()}, end{transports.bylevelEnd()};
             i != end; ++i) {
            Transport &t{i->getElement()};
            of << t.getType() << '\t' << t.getDistance() << '\t' << t.getName();

            auto timetable{t.getTimetable()};
            for (auto i{timetable.bylevelBegin()}, end{timetable.bylevelEnd()};
                 i != end; ++i)
                of << '\t' << i->getElement();

            of << '\n';
        }

        of << '\n';
    }
}
void Company::writeClient() {
    // std::ofstream of{CLIENT_FILE_PATH};
    std::ofstream of{"../../output/client.tsv"};

    if (of.fail())
        throw WriteError();

    for (Client *c : _clients) {
        of << c->getNIF() << '\t' << c->getName() << '\n';

        for (Ticket *t : c->getTickets())
            of << t->getFlight()->getID() << '\t' << t->getSeat() << '\n';

        of << '\n';
    }
}

void Company::populate() {
    readAirport();
    readPlane();
    readClient();
}
void Company::save() {
    writeAirport();
    writeClient();
    writePlane();
}

Plane *Company::createPlane(unsigned rows, unsigned columns, std::string plate,
                            std::string type) {
    Plane *plane = new Plane(_planes.size(), rows, columns, plate, type);
    _planes.push_back(plane);
    return plane;
}
void Company::updatePlane(Plane *plane, unsigned rows, unsigned columns) {
    if (rows)
        plane->setRows(rows);

    if (columns)
        plane->setColumns(columns);
}
void Company::deletePlane(Plane *plane) {
    bool deleted = false;
    for (size_t i{0}; i < _planes.size(); ++i) {
        if (_planes.at(i) == plane)
            deleted = true;
        else if (deleted) {
            _planes.at(i)->setID(i - 1);
            _planes.at(i - 1) = _planes.at(i);
        }
    }
    if (deleted) {
        _planes.pop_back();

        for (Flight *flight : plane->getFlights())
            deleteFlight(flight);

        delete plane;
    }
}

Flight *Company::createFlight(unsigned number, unsigned duration,
                              Airport *origin, Airport *dest,
                              std::string departure, Plane *plane) {
    Flight *flight = new Flight(_flights.size(), number, duration, origin, dest,
                                departure, plane);
    _flights.push_back(flight);
    createCart(flight);
    return flight;
}
void Company::updateFlight(Flight *flight, unsigned duration,
                           std::string origin, std::string dest,
                           std::string departure, unsigned plane) {
    if (duration)
        flight->setDuration(duration);

    if (origin != "") {
        Airport *o = findAirport(origin);

        if (!o)
            o = createAirport(origin);

        flight->setOrigin(o);
    }

    if (dest != "") {
        Airport *d = findAirport(dest);

        if (!d)
            d = createAirport(dest);

        flight->setDestination(d);
    }

    if (departure != "")
        flight->setDepartureDate(departure);

    flight->setPlane(_planes.at(plane));
}
void Company::deleteFlight(Flight *flight) {
    Cart *cart = findCart(flight);
    delete cart;

    bool deleted = false;
    for (size_t i{0}; i < _flights.size(); ++i) {
        if (_flights.at(i) == flight)
            deleted = true;
        else if (deleted) {
            _flights.at(i)->setID(i - 1);
            _flights.at(i - 1) = _flights.at(i);
        }
    }
    if (deleted) {
        _flights.pop_back();
        delete flight;
    }
}

Client *Company::createClient(unsigned nif, std::string name) {
    Client *client = new Client(_clients.size(), nif, name);
    _clients.push_back(client);
    return client;
}
void Company::updateClient(Client *client, std::string name) {
    if (name != "")
        client->setName(name);
}
void Company::deleteClient(Client *client) {
    bool deleted = false;
    for (size_t i{0}; i < _clients.size(); ++i) {
        if (_clients.at(i) == client)
            deleted = true;
        else if (deleted) {
            _clients.at(i)->setID(i - 1);
            _clients.at(i - 1) = _clients.at(i);
        }
    }
    if (deleted) {
        _clients.pop_back();
        delete client;
    }
}

Airport *Company::createAirport(std::string name) {
    Airport *airport = new Airport(_airports.size(), name);
    _airports.push_back(airport);
    return airport;
}
void Company::updateAirport(Airport *airport, std::string name) {
    if (name != "")
        airport->setName(name);
}
void Company::deleteAirport(Airport *airport) {
    bool deleted = false;
    for (size_t i{0}; i < _airports.size(); ++i) {
        if (_airports.at(i) == airport)
            deleted = true;
        else if (deleted) {
            _airports.at(i)->setID(i - 1);
            _airports.at(i - 1) = _airports.at(i);
        }
    }
    if (deleted) {
        _airports.pop_back();
        delete airport;
    }
}

Cart *Company::createCart(Flight *flight) {
    Cart *cart = new Cart(flight);
    _carts.push_back(cart);
    return cart;
}
void Company::updateCart(Cart *cart, unsigned newCartSize,
                         unsigned newTrolleySize, unsigned newStackSize) {
    if (newCartSize > 0)
        cart->setCartSize(newCartSize);

    if (newTrolleySize > 0)
        cart->setTrolleySize(newTrolleySize);

    if (newStackSize > 0)
        cart->setStackSize(newStackSize);
}

Flight *Company::findFlight(unsigned number) {
    for (Flight *f : _flights) {
        if (f->getNumber() == number) {
            return f;
        }
    }

    return nullptr;
}
Client *Company::findClient(unsigned nif) {
    for (Client *c : _clients) {
        if (c->getNIF() == nif) {
            return c;
        }
    }

    return nullptr;
}
Airport *Company::findAirport(std::string name) {
    for (Airport *a : _airports) {
        if (a->getName() == name) {
            return a;
        }
    }
    return nullptr;
}
Cart *Company::findCart(Flight *flight) {
    for (auto cart : _carts) {
        if (cart->getFlight() == flight) {
            return cart;
        }
    }

    return nullptr;
}
