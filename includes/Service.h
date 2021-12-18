#ifndef AED_PROJ_2021_SERVICE_H
#define AED_PROJ_2021_SERVICE_H

#include <string>

enum ServiceType { CLEANING, MAINTENANCE };

/**
 * @brief Represents a service.
 */
class Service {
private:
    const std::string _date, _worker;
    const ServiceType _type;

public:
    Service(ServiceType type, std::string date, std::string worker)
        : _worker(worker), _date(date), _type(type){};

    // Getters
    /**
     * @return This service's date.
     */
    std::string getDate() const { return _date; };
    /**
     * @return This service's worker.
     */
    std::string getWorker() const { return _worker; };
    /**
     * @return This service's type.
     */
    ServiceType getType() const { return _type; };
};

#endif // AED_PROJ_2021_SERVICE_H
