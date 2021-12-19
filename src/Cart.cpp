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