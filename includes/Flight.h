#ifndef AED_PROJ_2021_FLIGHT_H
#define AED_PROJ_2021_FLIGHT_H

#include <string>

class Flight {
private:
    unsigned number, duration;
    std::string departureDate, destination, origin;

public:
    // Constructors
    Flight() {
        this->origin = "";
        this->destination = "";
        this->departureDate = "";
        this->number = 0;
        this->duration = 0;
    };

    Flight(std::string origin, std::string destination, std::string departureDate, unsigned number, unsigned duration) {
        this->origin = "";
        this->destination = "";
        this->departureDate = "";
        this->number = 0;
        this->duration = 0;
    };

    // Getters
    unsigned getNumber() const { return this->number; };
    unsigned getDuration() const { return this->duration; };
    std::string getDepartureDate() const { return this->departureDate; };
    std::string getDestination() const { return this->destination; };
    std::string getOrigin() const { return this->origin; };

    // Setters
    void setNumber(unsigned n) { this->number = n; };
    void setDuration(unsigned dur) { this->duration = dur; };
    void setDepartureDate(std::string dep) { this->departureDate = dep; };
    void setDestination(std::string des) { this->destination = des; };
    void setOrigin(std::string org) { this->origin = org; };
};


#endif //AED_PROJ_2021_FLIGHT_H
