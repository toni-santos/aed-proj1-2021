#ifndef AED_PROJ_2021_TRANSPORT_H
#define AED_PROJ_2021_TRANSPORT_H

#include "BST.h"

#include <string>

enum TransportType { TRAIN, BUS, METRO };

/**
 * @brief Represents a land transport, like a train, bus or metro, near an
 *        airport.
 */
class Transport {
    unsigned _distance{};
    std::string _name{};
    TransportType _type{};
    BST<std::string> _timetable{};

public:
    Transport(TransportType type, unsigned distance, std::string name)
        : _type(type), _distance(distance), _name(name){};

    /**
     * @return This transport's name.
     */
    std::string getName() const { return _name; };
    /**
     * @return This transport's distance to the airport.
     */
    unsigned getDistance() const { return _distance; };
    /**
     * @return This transport's type.
     */
    TransportType getType() const { return _type; };
    /**
     * @return This transport's timetable.
     */
    BST<std::string> &getTimetable() { return _timetable; };

    void setName(std::string name) { _name = name; };

    /**
     * @brief Inserts a time into this transport's timetable.
     *
     * @param time The time to insert.
     */
    void insertTime(std::string time) { _timetable.insert(time); };

    /**
     * @param other the transport to be compared.
     * @return a boolean that verifies if this transport's distance (to the
     * airport) is less than another transport's (other's) distance.
     */
    bool operator<(const Transport &other) const {
        return _distance < other._distance;
    }
};

#endif // AED_PROJ_2021_TRANSPORT_H
