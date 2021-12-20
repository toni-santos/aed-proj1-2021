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
    /**
     * @brief The type of a stack of luggage.
     */
    using stackT = std::stack<Luggage *>;
    /**
     * @brief The type of a trolley.
     */
    using trolleyT = std::vector<stackT>;
    /**
     * @brief The type of the cart itself.
     */
    using cartT = std::list<trolleyT>;

    /**
     * @brief How many trolleys this cart has.
     */
    unsigned _cartSize;
    /**
     * @brief How many stacks each trolley has.
     */
    unsigned _trolleySize;
    /**
     * @brief How much luggage each stack has.
     */
    unsigned _stackSize;
    /**
     * @brief The cart itself.
     */
    cartT _cart{};
    /**
     * @brief The flight this cart is associated with.
     */
    Flight *_flight = nullptr;

public:
    /**
     * @brief Creates a new cart.
     *
     * @note Don't call this directly, use Company::createCart.
     *
     * @param flight The flight this cart will be associated with.
     * @param cartSize How many trolleys this cart will have.
     * @param trolleySize How many stacks each trolley will have.
     * @param stackSize How much luggage each stack will have.
     */
    Cart(Flight *flight, unsigned cartSize = 3, unsigned trolleySize = 4,
         unsigned stackSize = 5)
        : _cartSize(cartSize), _trolleySize(trolleySize), _stackSize(stackSize),
          _flight(flight),
          _cart(cartT{_cartSize, trolleyT{_trolleySize, stackT{}}}){};
    ~Cart();

    /**
     * @return How many trolleys this cart has.
     */
    unsigned getCapacity() const {
        return _cartSize * _trolleySize * _stackSize;
    };
    /**
     * @return How many stacks each trolley has.
     */
    unsigned getCartSize() const { return _cartSize; };
    /**
     * @return How many stacks each trolley has.
     */
    unsigned getTrolleySize() const { return _trolleySize; };
    /**
     * @return How much luggage each stack has.
     */
    unsigned getStackSize() const { return _stackSize; };
    /**
     * @return The flight this cart is associated with.
     */
    Flight *getFlight() const { return _flight; };
    /**
     * @return The cart itself.
     */
    cartT getCart() const { return _cart; };
    /**
     * @brief Sets how many stacks each trolley has.
     *
     * @param cartSize The new cart size.
     */
    void setCartSize(unsigned cartSize) { _cartSize = cartSize; };
    /**
     * @brief Sets how many stacks each trolley has.
     *
     * @param trolleySize The new trolley size.
     */
    void setTrolleySize(unsigned trolleySize) { _trolleySize = trolleySize; };
    /**
     * @brief Sets how much luggage each stack has.
     *
     * @param stackSize The new stack size.
     */
    void setStackSize(unsigned stackSize) { _stackSize = stackSize; };

    /**
     * @brief Adds luggage to the cart.
     *
     * @param luggage The luggage to add.
     */
    void addLuggage(Luggage *luggage);
    /**
     * @brief Empties the cart by moving all the luggage to the plane storage.
     */
    void unloadCart();
};

#endif // AED_PROJ_2021_CART_H