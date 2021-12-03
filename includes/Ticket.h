#ifndef AED_PROJ_2021_TICKET_H
#define AED_PROJ_2021_TICKET_H

class Ticket {
    const unsigned _id, _flightID;
    // TODO: prices (?)
    //unsigned _price;
public:
    Ticket(unsigned id, unsigned flightID):
        _id(id), _flightID(flightID) { };

    // Getters
    unsigned getID() const { return this->_id; }
    // unsigned getPrice() const { return this->_price; }

    // Setters
    // void setPrice(unsigned price) { _price = price; }
};


#endif //AED_PROJ_2021_TICKET_H
