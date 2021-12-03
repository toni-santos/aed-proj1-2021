#ifndef AED_PROJ_2021_SERVICE_H
#define AED_PROJ_2021_SERVICE_H

#include <string>

class Service {
private:
    const std::string _date, _worker;
    const unsigned int _type;

public:
    enum _types {cleaning = 0, maintenance};

    Service(unsigned int type, std::string date, std::string worker):
        _worker(worker), _date(date), _type(type) { };

    // Getters
    std::string getDate() { return _date; };
    std::string getWorker() { return _worker; };
    unsigned int getType() { return _type; };
};


#endif //AED_PROJ_2021_SERVICE_H
