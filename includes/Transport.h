#ifndef AED_PROJ_2021_TRANSPORT_H
#define AED_PROJ_2021_TRANSPORT_H

#include <string>

enum TransportType { TRAIN, BUS, METRO };

class Transport {
    unsigned _distance{};
    std::string _name{};
    TransportType _type{};

public:
    Transport(TransportType type, unsigned distance, std::string name)
        : _type(type), _distance(distance), _name(name){};

    std::string getName() const { return _name; };
    unsigned getDistance() const { return _distance; };
    TransportType getType() const { return _type; };

    bool operator<(const Transport &other) {
        return _distance < other._distance;
    }
};

#endif // AED_PROJ_2021_TRANSPORT_H
