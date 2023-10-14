#include "AVLNode.hpp"

template <typename T>
AVLNode<T>::AVLNode(const T& val) : data(val), left(nullptr), right(nullptr), height(1) {}

template <typename T>
AVLNode<T>::~AVLNode() {
    delete left;
    delete right;
}