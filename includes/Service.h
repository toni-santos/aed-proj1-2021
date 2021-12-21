#ifndef AED_PROJ_2021_SERVICE_H
#define AED_PROJ_2021_SERVICE_H

#include <string>

/**
 * @brief Holds the possible types of service.
 */
enum ServiceType {
    /**
     * @brief The plane will be cleaned.
     */
    CLEANING,
    /**
     * @brief The plane will have another type of work done.
     */
    MAINTENANCE
};

/**
 * @brief Represents a service.
 */
class Service {
private:
    /**
     * @brief When this service will be/has been done.
     */
    const std::string _date;
    /**
     * @brief Who will do/has done this service.
     */
    const std::string _worker;
    /**
     * @brief This service's type.
     */
    const ServiceType _type;

public:
    /**
     * @brief Creates a new service.
     *
     * @param type The type of service.
     * @param date When this service will be/has been done.
     * @param worker Who will do/has done this service.
     */
    Service(ServiceType type, std::string date, std::string worker)
        : _worker(worker), _date(date), _type(type){};

    // Getters
    /**
     * @return When this service will be/has been done.
     */
    std::string getDate() const { return _date; };
    /**
     * @return Who will do/has done this service.
     */
    std::string getWorker() const { return _worker; };
    /**
     * @return This service's type.
     */
    ServiceType getType() const { return _type; };
    /**
     * @return This service's type, in string form.
     */
    std::string getTypeStr() const {
        return _type == CLEANING ? "Cleaning" : "Maintenance";
    }
};

#endif // AED_PROJ_2021_SERVICE_H
