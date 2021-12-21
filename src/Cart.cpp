#include "../includes/Cart.h"

Cart::~Cart() {
    for (auto trolley : _cart) {
        for (auto stack : trolley) {
            while (!stack.empty()) {
                delete stack.top();
                stack.pop();
            }
        }
    }
}

void Cart::setSizes(unsigned cartSize, unsigned trolleySize,
                    unsigned stackSize) {
    _cartSize = cartSize;
    _trolleySize = trolleySize;
    _stackSize = stackSize;

    unloadCart();

    _cart = cartT{_cartSize, trolleyT{_trolleySize, stackT{}}};
}

void Cart::addLuggage(Luggage *luggage) {
    unsigned filled{0};

    for (auto &trolley : _cart) {
        for (auto &stack : trolley) {
            filled += stack.size();

            if (stack.size() <= _stackSize) {
                stack.push(luggage);

                if (filled + 1 == getCapacity())
                    unloadCart();

                return;
            }
        }
    }
}

void Cart::unloadCart() {
    for (auto trolley : _cart) {
        for (auto stack : trolley) {
            while (!stack.empty()) {
                _flight->addLuggage(stack.top());
                stack.pop();
            }
        }
    }
}
