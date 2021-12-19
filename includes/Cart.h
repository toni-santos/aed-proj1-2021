#ifndef AED_PROJ_2021_CART_H
#define AED_PROJ_2021_CART_H

class Cart;

#include "Flight.h"
#include "Luggage.h"

#include <list>
#include <stack>
#include <vector>

/**
 * @brief Represents a luggage cart.
 */
class Cart {
    using stackT = std::stack<Luggage *>;
    using trolleyT = std::vector<stackT>;
    using cartT = std::list<trolleyT>;

    unsigned _cartSize, _trolleySize, _stackSize;
    cartT _cart{};
    Flight *_flight = nullptr;

public:
    Cart(Flight *flight, unsigned cartSize = 3, unsigned trolleySize = 4,
         unsigned stackSize = 5)
        : _cartSize(cartSize), _trolleySize(trolleySize), _stackSize(stackSize),
          _flight(flight),
          _cart(cartT{_cartSize, trolleyT{_trolleySize, stackT{}}}){};
    ~Cart();

    /**
     * @return this cart's capacity.
     */
    unsigned getCapacity() const {
        return _cartSize * _trolleySize * _stackSize;
    };
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
     * @return the flight associated to this cart.
     */
    cartT getCart() const { return _cart; };
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
     * @brief empty the cart by storing all of the luggages in the plane of the
     * associated flight.
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