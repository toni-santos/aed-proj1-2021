#ifndef AED_PROJ_2021_SERVICE_H
#define AED_PROJ_2021_SERVICE_H

#include <string>

/**
 * @brief Class representing a service.
 */
class Service {
private:
    const std::string _date, _worker;
    const unsigned int _type;

public:
    enum _types { cleaning = 0, maintenance };

    Service(unsigned int type, std::string date, std::string worker)
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
    unsigned int getType() const { return _type; };
};

#endif // AED_PROJ_2021_SERVICE_H
