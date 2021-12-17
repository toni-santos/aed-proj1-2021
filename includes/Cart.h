#ifndef AED_PROJ_2021_CART_H
#define AED_PROJ_2021_CART_H

class Cart;

#include "Flight.h"
#include "Luggage.h"

#include <list>
#include <stack>
#include <vector>
/**
 * @brief Class representing a luggage cart.
 */
class Cart {
    unsigned _cartSize, _trolleySize, _stackSize;
    std::list<std::vector<std::stack<Luggage *>>> _cart;
    Flight *_flight;

public:
    Cart(Flight *flight, unsigned cartSize = 3, unsigned trolleySize = 4,
         unsigned stackSize = 5)
        : _cartSize(cartSize), _trolleySize(trolleySize), _stackSize(stackSize),
          _flight(flight){};

    /**
     * @return this cart's size.
     */
    unsigned getCartSize() const { return _cartSize; };
    /**
     * @return the size of this cart's trolley.
     */
    unsigned getTrolleySize() const { return _trolleySize; };
    /**
     * @return the size of the stack that's part of this cart's trolley.
     */
    unsigned getStackSize() const { return _stackSize; };
    /**
     * @return the flight associated to this cart.
     */
    Flight *getFlight() const { return _flight; };
    /**
     * @brief set this cart's size.
     *
     * @param cartSize the new cart size.
     */
    void setCartSize(unsigned cartSize) { _cartSize = cartSize; };
    /**
     * @brief set the size of this cart's trolley.
     *
     * @param trolleySize the new trolley size.
     */
    void setTrolleySize(unsigned trolleySize) { _trolleySize = trolleySize; };
    /**
     * @brief set the size of the stack that's part of this cart's trolley.
     *
     * @param stackSize the new stack size.
     */
    void setStackSize(unsigned stackSize) { _stackSize = stackSize; };

    /**
     * @brief add a luggage to the cart.
     *
     * @param luggage the new luggage.
     */
    void addLuggage(Luggage *luggage);
    /**
     * @brief empty the cart by storing all of the luggages in the plane of the associated flight.
     */
    void unloadCart();
    /**
     * @param cart the cart to be checked.
     * @return check if the this whole cart is full.
     */
    bool isFull(std::list<std::vector<std::stack<Luggage *>>> cart);
    /**
     * @param trolley the trolley to be checked.
     * @return check if this whole cart's trolley is full.
     */
    bool isFull(std::vector<std::stack<Luggage *>> trolley);
};

#endif // AED_PROJ_2021_CART_H