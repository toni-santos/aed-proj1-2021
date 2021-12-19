#ifndef AED_PROJ_2021_BST_H
#define AED_PROJ_2021_BST_H

#include <iostream>
#include <queue>
#include <stack>

template <class E> class BSTReverseInOrderIterator;
template <class E> class BSTInOrderIterator;
template <class E> class BSTPreOrderIterator;
template <class E> class BSTPostOrderIterator;
template <class E> class BSTByLevelIterator;
template <class E> class BST;

//---------------------- BinaryNode ----------------------
/**
 * @brief Represents a node in a binary tree.
 *
 * @tparam E The element type.
 */
template <class E> class BinaryNode {
    E _element;
    BinaryNode *_left = nullptr;
    BinaryNode *_right = nullptr;

public:
    BinaryNode(const E &el) : _element(el){};
    ~BinaryNode();

    /**
     * @return This node's element.
     */
    E &getElement() { return _element; };
    /**
     * @return The child to the left of this node.
     */
    BinaryNode *&getLeft() { return _left; };
    /**
     * @return The child to the right of this node.
     */
    BinaryNode *&getRight() { return _right; };

    /**
     * @brief Set this node's element.
     *
     * @param el The new element.
     */
    void setElement(const E &el) { _element = el; };

    /**
     * @brief Inserts a new child to the left of this node.
     *
     * @note If there was already a child to the left of this node, it and its
     *       children are deleted.
     *
     * @param el The element to insert
     */
    void insertLeft(const E &el);
    /**
     * @brief Inserts a new child to the right of this node.
     *
     * @note If there was already a child to the right of this node, it and its
     *       children are deleted.
     *
     * @param el The element to insert
     */
    void insertRight(const E &el);
    /**
     * @brief Deletes the child to the left of this node.
     */
    void deleteLeft();
    /**
     * @brief Deletes the child to the right of this node.
     */
    void deleteRight();

    /**
     * @brief Clones this node and all its children.
     *
     * @return A new node.
     */
    BinaryNode<E> *clone();
};

template <class E> BinaryNode<E>::~BinaryNode() {
    deleteLeft();
    deleteRight();
}

template <class E> void BinaryNode<E>::insertLeft(const E &el) {
    deleteLeft();
    _left = new BinaryNode<E>(el);
}
template <class E> void BinaryNode<E>::insertRight(const E &el) {
    deleteRight();
    _right = new BinaryNode<E>(el);
}

template <class E> void BinaryNode<E>::deleteLeft() {
    if (_left)
        delete _left;
}
template <class E> void BinaryNode<E>::deleteRight() {
    if (_right)
        delete _right;
}

template <class E> BinaryNode<E> *BinaryNode<E>::clone() {
    BinaryNode<E> *n = new BinaryNode<E>(_element);

    if (_left)
        n->_left = _left->clone();
    if (_right)
        n->_right = _right->clone();

    return n;
}

//-------------------------- BST -------------------------
/**
 * @brief Implements a binary search tree.
 *
 * @tparam E The element type.
 */
template <class E> class BST {
    BinaryNode<E> *_root = nullptr;

    /**
     * @brief Gets the minimum element in a subtree.
     *
     * @param t The root of the subtree.
     *
     * @return The node with the minimum element.
     */
    BinaryNode<E> *min(BinaryNode<E> *t) const;
    /**
     * @brief Gets the maximum element in a subtree.
     *
     * @param t The root of the subtree.
     *
     * @return The node with the maximum element.
     */
    BinaryNode<E> *max(BinaryNode<E> *t) const;

    /**
     * @brief Searches for an element equivelement to the given value in a
     *        subtree.
     *
     * @tparam A type comparable with the element type, that is, implements
     *         C < E and E < C.
     * @param x The value to search for.
     * @param t The root of the subtree.
     * @return The node with the element searched for, or nullptr if not found.
     */
    template <class C> BinaryNode<E> *find(const C &x, BinaryNode<E> *t);

    /**
     * @brief Inserts an element into a subtree.
     *
     * @param x The element to insert.
     * @param t The root of the subtree.
     * @return true if inserted.
     * @return false if already in subtree.
     */
    bool insert(const E &x, BinaryNode<E> *t);
    /**
     * @brief Removes the element equivelent to the given value from a subtree.
     *
     * @tparam A type comparable with the element type, that is, implements
     *         C < E and E < C.
     * @param x The value to search for.
     * @param t The root of the subtree.
     * @return true if removed.
     * @return false if not in subtree.
     */
    template <class C> bool remove(const C &x, BinaryNode<E> *&t);

public:
    BST(){};
    BST(const BST<E> &bst) { *this = bst; };
    ~BST() { makeEmpty(); };

    /**
     * @return The root of this tree.
     */
    BinaryNode<E> *getRoot() const { return _root; };

    /**
     * @brief Checks if this tree is empty.
     *
     * @return true if this tree is empty.
     */
    bool empty() const;
    /**
     * @brief Empties this tree.
     */
    void makeEmpty();

    /**
     * @brief Gets the minimum element in the tree.
     *
     * @return The node with the minimum element.
     */
    BinaryNode<E> *min() const;
    /**
     * @brief Gets the maximum element in the tree.
     *
     * @return The node with the maximum element.
     */
    BinaryNode<E> *max() const;

    /**
     * @brief Searches for an element equivelement to the given value.
     *
     * @tparam A type comparable with the element type, that is, implements
     *         C < E and E < C.
     * @param x The value to search for.
     * @return The node with the element searched for, or nullptr if not found.
     */
    template <class C> BinaryNode<E> *find(const C &x);

    /**
     * @brief Inserts an element into the tree.
     *
     * @param x The element to insert.
     * @return true if inserted.
     * @return false if already in tree.
     */
    bool insert(const E &x);
    /**
     * @brief Removes the element equivelent to the given value from the tree.
     *
     * @tparam A type comparable with the element type, that is, implements
     *         C < E and E < C.
     * @param x The value to search for.
     * @return true if removed.
     * @return false if not in tree.
     */
    template <class C> bool remove(const C &x);

    /**
     * @return An in-order iterator for this tree.
     */
    BSTInOrderIterator<E> inorderBegin() const;
    /**
     * @return An in-order iterator for this tree that points to after the last
     *         element.
     */
    BSTInOrderIterator<E> inorderEnd() const;
    /**
     * @return A reverse in-order iterator for this tree.
     */
    BSTReverseInOrderIterator<E> rinorderBegin() const;
    /**
     * @return A reverse in-order iterator for this tree that points to after
     * the last element.
     */
    BSTReverseInOrderIterator<E> rinorderEnd() const;
    /**
     * @return A pre-order iterator for this tree.
     */
    BSTPreOrderIterator<E> preorderBegin() const;
    /**
     * @return A pre-order iterator for this tree that points to after the last
     *         element.
     */
    BSTPreOrderIterator<E> preorderEnd() const;
    /**
     * @return A post-order iterator for this tree.
     */
    BSTPostOrderIterator<E> postorderBegin() const;
    /**
     * @return A post-order iterator for this tree that points to after the last
     *         element.
     */
    BSTPostOrderIterator<E> postorderEnd() const;
    /**
     * @return A by-level iterator for this tree.
     */
    BSTByLevelIterator<E> bylevelBegin() const;
    /**
     * @return A by-level iterator for this tree that points to after the last
     *         element.
     */
    BSTByLevelIterator<E> bylevelEnd() const;

    /**
     * @note Same as inorderBegin.
     *
     * @return An in-order iterator for this tree.
     */
    auto begin() const { return inorderBegin(); };
    /**
     * @note Same as inorderEnd.
     *
     * @return An in-order iterator for this tree that points to after the last
     *         element.
     */
    auto end() const { return inorderEnd(); };
    /**
     * @note Same as rinorderBegin.
     *
     * @return A reverse in-order iterator for this tree.
     */
    auto rbegin() const { return rinorderBegin(); };
    /**
     * @note Same as rinorderEnd.
     *
     * @return A reverse in-order iterator for this tree that points to after
     *         the last element.
     */
    auto rend() const { return rinorderEnd(); };

    const BST<E> &operator=(const BST<E> &bst);
};

template <class E> bool BST<E>::empty() const { return !_root; }
template <class E> void BST<E>::makeEmpty() {
    delete _root;
    _root = nullptr;
}

template <class E> BinaryNode<E> *BST<E>::min(BinaryNode<E> *t) const {
    if (!t)
        return nullptr;
    if (!t->getLeft())
        return t;
    return min(t->getLeft());
}
template <class E> BinaryNode<E> *BST<E>::min() const { return min(_root); }

template <class E> BinaryNode<E> *BST<E>::max(BinaryNode<E> *t) const {
    if (!t)
        return nullptr;
    if (!t->getRight())
        return t;
    return max(t->getRight());
}
template <class E> BinaryNode<E> *BST<E>::max() const { return max(_root); }

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
template <class E> bool BST<E>::insert(const E &x) {
    if (!_root) {
        _root = new BinaryNode<E>(x);
        return true;
    }

    return insert(x, _root);
}

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
    return BSTInOrderIterator<E>(std::stack<BinaryNode<E> *>{});
}
template <class E> BSTReverseInOrderIterator<E> BST<E>::rinorderBegin() const {
    return {*this};
}
template <class E> BSTReverseInOrderIterator<E> BST<E>::rinorderEnd() const {
    return BSTReverseInOrderIterator<E>(std::stack<BinaryNode<E> *>{});
}
template <class E> BSTPreOrderIterator<E> BST<E>::preorderBegin() const {
    return {*this};
}
template <class E> BSTPreOrderIterator<E> BST<E>::preorderEnd() const {
    return BSTPreOrderIterator<E>(std::stack<BinaryNode<E> *>{});
}
template <class E> BSTPostOrderIterator<E> BST<E>::postorderBegin() const {
    return {*this};
}
template <class E> BSTPostOrderIterator<E> BST<E>::postorderEnd() const {
    return BSTPostOrderIterator<E>(std::stack<BinaryNode<E> *>{},
                                   std::stack<bool>{});
}
template <class E> BSTByLevelIterator<E> BST<E>::bylevelBegin() const {
    return {*this};
}
template <class E> BSTByLevelIterator<E> BST<E>::bylevelEnd() const {
    return BSTByLevelIterator<E>(std::queue<BinaryNode<E> *>{});
}

template <class E> const BST<E> &BST<E>::operator=(const BST<E> &bst) {
    if (this != &bst) {
        makeEmpty();
        if (bst.getRoot())
            _root = bst.getRoot()->clone();
    }
    return *this;
}

//----------------- BSTPostOrderIterator -----------------
/**
 * @brief An iterator that loops over a binary search tree in post order.
 *
 * @tparam E The element type.
 */
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
    if (bt.getRoot())
        slideDown(bt.getRoot());
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
/**
 * @brief An iterator that loops over a binary search tree in pre order.
 *
 * @tparam E The element type.
 */
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
    if (bt.getRoot())
        _stack.push(bt.getRoot());
}

// Prefix
template <class E>
BSTPreOrderIterator<E> &BSTPreOrderIterator<E>::operator++() {
    pointer current = _stack.top();
    pointer next = current->getLeft();
    if (next)
        _stack.push(next);
    else {
        while (!_stack.empty()) {
            current = _stack.top();
            _stack.pop();
            next = current->getRight();
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
/**
 * @brief An iterator that loops over a binary search tree in order.
 *
 * @tparam E The element type.
 */
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
    if (bt.getRoot())
        slideLeft(bt.getRoot());
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
    BinaryNode<E> *next = current->getRight();
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

//------------------ BSTReverseInOrderIterator ------------------
/**
 * @brief An iterator that loops over a binary search tree in reverse order.
 *
 * @tparam E The element type.
 */
template <class E> class BSTReverseInOrderIterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = BinaryNode<E>;
    using pointer = value_type *;
    using reference = value_type &;

    std::stack<pointer> _stack;
    void slideRight(BinaryNode<E> *n);

public:
    BSTReverseInOrderIterator(const BST<E> &bt);
    BSTReverseInOrderIterator(std::stack<pointer> stack);

    reference operator*() const;
    pointer operator->();
    BSTReverseInOrderIterator &operator++();
    BSTReverseInOrderIterator operator++(int);
    bool operator==(const BSTReverseInOrderIterator<E> &other);
    bool operator!=(const BSTReverseInOrderIterator<E> &other);
};

template <class E>
BSTReverseInOrderIterator<E>::BSTReverseInOrderIterator(
    std::stack<pointer> stack)
    : _stack(stack){};

template <class E>
BSTReverseInOrderIterator<E>::BSTReverseInOrderIterator(const BST<E> &bt) {
    if (bt.getRoot())
        slideRight(bt.getRoot());
}

template <class E> void BSTReverseInOrderIterator<E>::slideRight(pointer n) {
    while (n) {
        _stack.push(n);
        n = n->getRight();
    }
}

// Prefix
template <class E>
BSTReverseInOrderIterator<E> &BSTReverseInOrderIterator<E>::operator++() {
    BinaryNode<E> *current = _stack.top();
    _stack.pop();
    BinaryNode<E> *next = current->getLeft();
    if (next)
        slideRight(next);

    return *this;
}

// Postfix
template <class E>
BSTReverseInOrderIterator<E> BSTReverseInOrderIterator<E>::operator++(int) {
    BSTReverseInOrderIterator<E> temp = *this;
    ++(*this);
    return temp;
}

template <class E>
typename BSTReverseInOrderIterator<E>::reference
BSTReverseInOrderIterator<E>::operator*() const {
    return *_stack.top();
}

template <class E>
typename BSTReverseInOrderIterator<E>::pointer
BSTReverseInOrderIterator<E>::operator->() {
    return _stack.top();
}

template <class E>
bool BSTReverseInOrderIterator<E>::operator==(
    const BSTReverseInOrderIterator<E> &other) {
    return _stack == other._stack;
};

template <class E>
bool BSTReverseInOrderIterator<E>::operator!=(
    const BSTReverseInOrderIterator<E> &other) {
    return _stack != other._stack;
};

//------------------ BSTByLevelIterator ------------------
/**
 * @brief An iterator that loops over a binary search tree by level.
 *
 * @tparam E The element type.
 */
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
    if (bt.getRoot())
        _queue.push(bt.getRoot());
}

// Prefix
template <class E> BSTByLevelIterator<E> &BSTByLevelIterator<E>::operator++() {
    pointer current = _queue.front();
    _queue.pop();
    pointer next = current->getLeft();
    if (next)
        _queue.push(next);
    next = current->getRight();
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
