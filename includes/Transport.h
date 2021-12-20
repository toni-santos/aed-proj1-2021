#ifndef AED_PROJ_2021_TRANSPORT_H
#define AED_PROJ_2021_TRANSPORT_H

#include "BST.h"

#include <string>

/**
 * @brief Holds the possible land transport types.
 */
enum TransportType {
    /**
     * @brief A [train](https://en.wikipedia.org/wiki/Train).
     */
    TRAIN,
    /**
     * @brief A [bus](https://en.wikipedia.org/wiki/Bus).
     */
    BUS,
    /**
     * @brief A [subway](https://en.wikipedia.org/wiki/Rapid_transit).
     */
    SUBWAY
};

/**
 * @brief Represents a land transport, like a train, bus or metro, near an
 *        airport.
 */
class Transport {
    /**
     * @brief This transport's distance to the airport, in meters.
     */
    unsigned _distance{};
    /**
     * @brief This transport's name.
     */
    std::string _name{};
    /**
     * @brief This transport's type.
     */
    TransportType _type{};
    /**
     * @brief This transport's timetable.
     */
    BST<std::string> _timetable{};

public:
    /**
     * @brief Creates a new land transport.
     *
     * @param type The type of transport.
     * @param distance The dinstance to the nearest airport, in meters.
     * @param name The transport's name.
     */
    Transport(TransportType type, unsigned distance, std::string name)
        : _type(type), _distance(distance), _name(name){};

    /**
     * @return This transport's name.
     */
    std::string getName() const { return _name; };
    /**
     * @return This transport's distance to the airport, in meters.
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

    /**
     * @brief Sets this transport's name.
     *
     * @param name The new name.
     */
    void setName(std::string name) { _name = name; };

    /**
     * @brief Inserts a time into this transport's timetable.
     *
     * @param time The time to insert.
     */
    void insertTime(std::string time) { _timetable.insert(time); };

    /**
     * @brief Compares two transports based on distance.
     *
     * @param other The other transport.
     * @return true if the first transport is closer to the airport.
     * @return false otherwise.
     */
    bool operator<(const Transport &other) const {
        return _distance < other._distance;
    }
};

#endif // AED_PROJ_2021_TRANSPORT_H
