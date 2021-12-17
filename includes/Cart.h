#ifndef AED_PROJ_2021_CART_H
#define AED_PROJ_2021_CART_H

class Cart;

#include "Flight.h"
#include "Luggage.h"

#include <list>
#include <stack>
#include <vector>

class Cart {
    unsigned _cartSize, _trolleySize, _stackSize;
    std::list<std::vector<std::stack<Luggage *>>> _cart;
    Flight *_flight;

public:
    Cart(Flight *flight, unsigned cartSize = 3, unsigned trolleySize = 4,
         unsigned stackSize = 5)
        : _cartSize(cartSize), _trolleySize(trolleySize), _stackSize(stackSize),
          _flight(flight){};

    unsigned getCartSize() const { return _cartSize; };
    unsigned getTrolleySize() const { return _trolleySize; };
    unsigned getStackSize() const { return _stackSize; };
    Flight *getFlight() const { return _flight; };

    void setCartSize(unsigned cartSize) { _cartSize = cartSize; };
    void setTrolleySize(unsigned trolleySize) { _trolleySize = trolleySize; };
    void setStackSize(unsigned stackSize) { _stackSize = stackSize; };

    void addLuggage(Luggage *luggage);
    void unloadCart();

    bool isFull(std::list<std::vector<std::stack<Luggage *>>> cart);
    bool isFull(std::vector<std::stack<Luggage *>> trolley);
};

#endif // AED_PROJ_2021_CART_H