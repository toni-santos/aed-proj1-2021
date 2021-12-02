#ifndef AED_PROJ_2021_PLANE_H
#define AED_PROJ_2021_PLANE_H

#include <string>

class Plane {
private:
    std::string plate, type;
    unsigned capacity;
public:
    // Constructors
    Plane() {
        this->capacity = 0;
        this->plate = "";
        this->type = "";
    };

    Plane(std::string plate, std::string type, unsigned capacity) {
        this->capacity = capacity;
        this->plate = plate;
        this->type = type;
    };

    // Getters
    unsigned getCapacity() const { return this->capacity; };
    std::string getPlate() const { return this->plate; };
    std::string getType() const { return this->type; };

    // Setters
    void setCapacity(unsigned cap) { this->capacity = cap; };
    void setPlate(std::string pl) { this->plate = pl; };
    void setType(std::string type) { this->type = type; };
};


#endif //AED_PROJ_2021_PLANE_H
