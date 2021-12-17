#include "../includes/Cart.h"

void Cart::addLuggage(Luggage *luggage) {
    if (!isFull(_cart)) {
        for (auto trolley : _cart) {
            if (!isFull(trolley)) {
                for (auto stack : trolley) {
                    if (stack.size() <= _stackSize) {
                        stack.push(luggage);
                        return;
                    }
                }
            }
        }
    }

    unloadCart();
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

bool Cart::isFull(std::list<std::vector<std::stack<Luggage *>>> cart) {
    if (cart.size() <= _cartSize) {
        for (auto trolley : cart) {
            if (!isFull(trolley) && trolley.size() <= _trolleySize) {
                return false;
            }
        }
    }

    return true;
}

bool Cart::isFull(std::vector<std::stack<Luggage *>> trolley) {
    for (auto stack : trolley) {
        if (stack.size() <= _stackSize) {
            return false;
        }
    }

    return true;
}