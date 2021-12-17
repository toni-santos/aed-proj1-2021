#ifndef AED_PROJ_2021_BST_H
#define AED_PROJ_2021_BST_H

#include <iostream>
#include <queue>
#include <stack>

template <class E> class BSTInOrderIterator;
template <class E> class BSTPreOrderIterator;
template <class E> class BSTPostOrderIterator;
template <class E> class BSTByLevelIterator;
template <class E> class BST;

//---------------------- BinaryNode ----------------------
template <class E> class BinaryNode {
    E _element;
    BinaryNode *_left;
    BinaryNode *_right;

public:
    BinaryNode(const E &el) : _element(el){};
    ~BinaryNode();

    E getElement() const { return _element; };
    BinaryNode *getLeft() const { return _left; };
    BinaryNode *getRight() const { return _right; };

    void setElement(const E &el) { _element = el; };

    void insertLeft(const E &el);
    void insertRight(const E &el);
    void deleteLeft();
    void deleteRight();
};

template <class E> BinaryNode<E>::~BinaryNode() {
    deleteLeft();
    deleteRight();
}

template <class E> void BinaryNode<E>::insertLeft(const E &el) {
    deleteLeft();
    _left = new BinaryNode(el);
}
template <class E> void BinaryNode<E>::insertRight(const E &el) {
    deleteRight();
    _right = new BinaryNode(el);
}

template <class E> void BinaryNode<E>::deleteLeft() {
    if (_left)
        delete _left;
}
template <class E> void BinaryNode<E>::deleteRight() {
    if (_right)
        delete _right;
}

//-------------------------- BST -------------------------
template <class E> class BST {
    BinaryNode<E> *_root;

    BinaryNode<E> min(BinaryNode<E> *t) const;
    BinaryNode<E> max(BinaryNode<E> *t) const;

    template <class C> BinaryNode<E> *find(const C &x, BinaryNode<E> *t);

    bool insert(const E &x, BinaryNode<E> *t);
    template <class C> bool remove(const C &x, BinaryNode<E> *&t);

public:
    BST(){};
    ~BST() { makeEmpty(); };

    BinaryNode<E> *getRoot() const { return _root; };

    bool empty() const;
    void makeEmpty();

    BinaryNode<E> min() const;
    BinaryNode<E> max() const;

    template <class C> BinaryNode<E> *find(const C &x);

    bool insert(const E &x);
    template <class C> bool remove(const C &x);

    BSTInOrderIterator<E> inorderBegin() const;
    BSTInOrderIterator<E> inorderEnd() const;
    BSTPreOrderIterator<E> preorderBegin() const;
    BSTPreOrderIterator<E> preorderEnd() const;
    BSTPostOrderIterator<E> postorderBegin() const;
    BSTPostOrderIterator<E> postorderEnd() const;
    BSTByLevelIterator<E> bylevelBegin() const;
    BSTByLevelIterator<E> bylevelEnd() const;

    auto begin() const { return inorderBegin(); };
    auto end() const { return inorderEnd(); };
};

template <class E> bool BST<E>::empty() const { return !_root; }
template <class E> void BST<E>::makeEmpty() {
    delete _root;
    _root = nullptr;
}

template <class E> BinaryNode<E> BST<E>::min(BinaryNode<E> *t) const {
    if (!t)
        return nullptr;
    if (!t->getLeft())
        return t;
    return findMin(t->getLeft());
}
template <class E> BinaryNode<E> BST<E>::min() const { return max(_root); }

template <class E> BinaryNode<E> BST<E>::max(BinaryNode<E> *t) const {
    if (!t)
        return nullptr;
    if (!t->getRight())
        return t;
    return findMin(t->getRight());
}
template <class E> BinaryNode<E> BST<E>::max() const { return max(_root); }

template <class E>
template <class C>
BinaryNode<E> *BST<E>::find(const C &x, BinaryNode<E> *t) {
    if (!t)
        return nullptr;
    else if (x < t->getElement())
        return find(x, t->getLeft());
    else if (t->getElement() < x)
        return find(x, t->getRight());
    else
        return t;
}
template <class E> template <class C> BinaryNode<E> *BST<E>::find(const C &x) {
    return find(x, _root);
}

template <class E> bool BST<E>::insert(const E &x, BinaryNode<E> *t) {
    if (x < t->getElement()) {
        if (t->getLeft()) {
            return insert(x, t->getLeft());
        } else {
            t->insertLeft(x);
            return true;
        }
    } else if (t->getElement() < x) {
        if (t->getRight()) {
            return insert(x, t->getRight());
        } else {
            t->insertRight(x);
            return true;
        }
    } else {
        return false; // Duplicate; do nothing
    }
}
template <class E> bool BST<E>::insert(const E &x) { return insert(x, _root); }

template <class E>
template <class C>
bool BST<E>::remove(const C &x, BinaryNode<E> *&t) {
    if (t == nullptr)
        return false; // Item not found; do nothing

    if (x < t->getElement())
        return remove(x, t->getLeft());

    else if (t->getElement() < x)
        return remove(x, t->getRight());

    else if (t->getLeft() && t->getRight()) { // Two children
        t->setElement(min(t->getRight())->getElement());
        return remove(t->getElement(), t->getRight());

    } else {
        BinaryNode<E> *oldNode = t;
        t = t->getLeft() ? t->getLeft() : t->getRight();
        delete oldNode;
        return true;
    }
}
template <class E> template <class C> bool BST<E>::remove(const C &x) {
    return remove(x, _root);
}

template <class E> BSTInOrderIterator<E> BST<E>::inorderBegin() const {
    return {*this};
}
template <class E> BSTInOrderIterator<E> BST<E>::inorderEnd() const {
    return {};
}
template <class E> BSTPreOrderIterator<E> BST<E>::preorderBegin() const {
    return {*this};
}
template <class E> BSTPreOrderIterator<E> BST<E>::preorderEnd() const {
    return {};
}
template <class E> BSTPostOrderIterator<E> BST<E>::postorderBegin() const {
    return {*this};
}
template <class E> BSTPostOrderIterator<E> BST<E>::postorderEnd() const {
    return {};
}
template <class E> BSTByLevelIterator<E> BST<E>::bylevelBegin() const {
    return {*this};
}
template <class E> BSTByLevelIterator<E> BST<E>::bylevelEnd() const {
    return {};
}

//----------------- BSTPostOrderIterator -----------------
template <class E> class BSTPostOrderIterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = BinaryNode<E>;
    using pointer = value_type *;
    using reference = value_type &;

    std::stack<pointer> _stack;
    std::stack<bool> _visitedStack;
    void slideDown(BinaryNode<E> *n);

public:
    BSTPostOrderIterator(const BST<E> &bt);
    BSTPostOrderIterator(std::stack<pointer> stack, std::stack<bool> vstack);

    reference operator*() const;
    pointer operator->();
    BSTPostOrderIterator &operator++();
    BSTPostOrderIterator operator++(int);
    bool operator==(const BSTPostOrderIterator<E> &other);
    bool operator!=(const BSTPostOrderIterator<E> &other);
};

template <class E>
BSTPostOrderIterator<E>::BSTPostOrderIterator(std::stack<pointer> stack,
                                              std::stack<bool> vstack)
    : _stack(stack), _visitedStack(vstack){};

template <class E>
BSTPostOrderIterator<E>::BSTPostOrderIterator(const BST<E> &bt) {
    if (bt._root)
        slideDown(bt._root);
}

template <class E> void BSTPostOrderIterator<E>::slideDown(pointer n) {
    while (n) {
        _stack.push(n);
        if (n->left) {
            _visitedStack.push(false);
            n = n->left;
        } else if (n->right) {
            _visitedStack.push(true);
            n = n->right;
        } else {
            _visitedStack.push(true);
            break;
        }
    }
}

// Prefix
template <class E>
BSTPostOrderIterator<E> &BSTPostOrderIterator<E>::operator++() {
    _stack.pop();
    _visitedStack.pop();

    if ((!_stack.empty()) && (_visitedStack.top() == false)) {
        _visitedStack.pop();
        _visitedStack.push(true);
        slideDown(_stack.top()->right);
    }

    return *this;
}

// Postfix
template <class E>
BSTPostOrderIterator<E> BSTPostOrderIterator<E>::operator++(int) {
    BSTPostOrderIterator<E> temp = *this;
    ++(*this);
    return temp;
}

template <class E>
typename BSTPostOrderIterator<E>::reference
BSTPostOrderIterator<E>::operator*() const {
    return *_stack.top();
}

template <class E>
typename BSTPostOrderIterator<E>::pointer
BSTPostOrderIterator<E>::operator->() {
    return _stack.top();
}

template <class E>
bool BSTPostOrderIterator<E>::operator==(const BSTPostOrderIterator<E> &other) {
    return _stack == other._stack && _visitedStack == other._visitedStack;
};

template <class E>
bool BSTPostOrderIterator<E>::operator!=(const BSTPostOrderIterator<E> &other) {
    return _stack != other._stack && _visitedStack != other._visitedStack;
};

//----------------- BSTPreOrderIterator ------------------
template <class E> class BSTPreOrderIterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = BinaryNode<E>;
    using pointer = value_type *;
    using reference = value_type &;

    std::stack<pointer> _stack;

public:
    BSTPreOrderIterator(const BST<E> &bt);
    BSTPreOrderIterator(std::stack<pointer> stack);

    reference operator*() const;
    pointer operator->();
    BSTPreOrderIterator &operator++();
    BSTPreOrderIterator operator++(int);
    bool operator==(const BSTPreOrderIterator<E> &other);
    bool operator!=(const BSTPreOrderIterator<E> &other);
};

template <class E>
BSTPreOrderIterator<E>::BSTPreOrderIterator(std::stack<pointer> stack)
    : _stack(stack){};

template <class E>
BSTPreOrderIterator<E>::BSTPreOrderIterator(const BST<E> &bt) {
    if (bt._root)
        _stack.push(bt._root);
}

// Prefix
template <class E>
BSTPreOrderIterator<E> &BSTPreOrderIterator<E>::operator++() {
    pointer current = _stack.top();
    pointer next = current->left;
    if (next)
        _stack.push(next);
    else {
        while (!_stack.empty()) {
            current = _stack.top();
            _stack.pop();
            next = current->right;
            if (next) {
                _stack.push(next);
                break;
            }
        }
    }

    return *this;
}

// Postfix
template <class E>
BSTPreOrderIterator<E> BSTPreOrderIterator<E>::operator++(int) {
    BSTPreOrderIterator<E> temp = *this;
    ++(*this);
    return temp;
}

template <class E>
typename BSTPreOrderIterator<E>::reference
BSTPreOrderIterator<E>::operator*() const {
    return *_stack.top();
}

template <class E>
typename BSTPreOrderIterator<E>::pointer BSTPreOrderIterator<E>::operator->() {
    return _stack.top();
}

template <class E>
bool BSTPreOrderIterator<E>::operator==(const BSTPreOrderIterator<E> &other) {
    return _stack == other._stack;
};

template <class E>
bool BSTPreOrderIterator<E>::operator!=(const BSTPreOrderIterator<E> &other) {
    return _stack != other._stack;
};

//------------------ BSTInOrderIterator ------------------
template <class E> class BSTInOrderIterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = BinaryNode<E>;
    using pointer = value_type *;
    using reference = value_type &;

    std::stack<pointer> _stack;
    void slideLeft(BinaryNode<E> *n);

public:
    BSTInOrderIterator(const BST<E> &bt);
    BSTInOrderIterator(std::stack<pointer> stack);

    reference operator*() const;
    pointer operator->();
    BSTInOrderIterator &operator++();
    BSTInOrderIterator operator++(int);
    bool operator==(const BSTInOrderIterator<E> &other);
    bool operator!=(const BSTInOrderIterator<E> &other);
};

template <class E>
BSTInOrderIterator<E>::BSTInOrderIterator(std::stack<pointer> stack)
    : _stack(stack){};

template <class E> BSTInOrderIterator<E>::BSTInOrderIterator(const BST<E> &bt) {
    if (bt._root)
        slideLeft(bt._root);
}

template <class E> void BSTInOrderIterator<E>::slideLeft(pointer n) {
    while (n) {
        _stack.push(n);
        n = n->getLeft();
    }
}

// Prefix
template <class E> BSTInOrderIterator<E> &BSTInOrderIterator<E>::operator++() {
    BinaryNode<E> *current = _stack.top();
    _stack.pop();
    BinaryNode<E> *next = current->right;
    if (next)
        slideLeft(next);

    return *this;
}

// Postfix
template <class E>
BSTInOrderIterator<E> BSTInOrderIterator<E>::operator++(int) {
    BSTInOrderIterator<E> temp = *this;
    ++(*this);
    return temp;
}

template <class E>
typename BSTInOrderIterator<E>::reference
BSTInOrderIterator<E>::operator*() const {
    return *_stack.top();
}

template <class E>
typename BSTInOrderIterator<E>::pointer BSTInOrderIterator<E>::operator->() {
    return _stack.top();
}

template <class E>
bool BSTInOrderIterator<E>::operator==(const BSTInOrderIterator<E> &other) {
    return _stack == other._stack;
};

template <class E>
bool BSTInOrderIterator<E>::operator!=(const BSTInOrderIterator<E> &other) {
    return _stack != other._stack;
};

//------------------ BSTByLevelIterator ------------------
template <class E> class BSTByLevelIterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = BinaryNode<E>;
    using pointer = value_type *;
    using reference = value_type &;

    std::queue<pointer> _queue;

public:
    BSTByLevelIterator(const BST<E> &bt);
    BSTByLevelIterator(std::queue<pointer> queue);

    reference operator*() const;
    pointer operator->();
    BSTByLevelIterator &operator++();
    BSTByLevelIterator operator++(int);
    bool operator==(const BSTByLevelIterator<E> &other);
    bool operator!=(const BSTByLevelIterator<E> &other);
};

template <class E>
BSTByLevelIterator<E>::BSTByLevelIterator(std::queue<pointer> queue)
    : _queue(queue){};

template <class E> BSTByLevelIterator<E>::BSTByLevelIterator(const BST<E> &bt) {
    if (bt._root)
        _queue.push(bt._root);
}

// Prefix
template <class E> BSTByLevelIterator<E> &BSTByLevelIterator<E>::operator++() {
    pointer current = _queue.front();
    _queue.pop();
    pointer next = current->left;
    if (next)
        _queue.push(next);
    next = current->_right;
    if (next)
        _queue.push(next);

    return *this;
}

// Postfix
template <class E>
BSTByLevelIterator<E> BSTByLevelIterator<E>::operator++(int) {
    BSTByLevelIterator<E> temp = *this;
    ++(*this);
    return temp;
}

template <class E>
typename BSTByLevelIterator<E>::reference
BSTByLevelIterator<E>::operator*() const {
    return *_queue.front();
}

template <class E>
typename BSTByLevelIterator<E>::pointer BSTByLevelIterator<E>::operator->() {
    return _queue.front();
}

template <class E>
bool BSTByLevelIterator<E>::operator==(const BSTByLevelIterator<E> &other) {
    return _queue == other._queue;
};

template <class E>
bool BSTByLevelIterator<E>::operator!=(const BSTByLevelIterator<E> &other) {
    return _queue != other._queue;
};

#endif // AED_PROJ_2021_BST_H
