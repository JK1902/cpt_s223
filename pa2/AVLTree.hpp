cpp
#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    void insert(const T& value) {
        root = insert(root, value);
    }

    int height() const {
        return height(root);
    }

    bool validate() const {
        return validate(root);
    }

    bool contains(const T& value) const {
        return contains(root, value);
    }

private:
    struct Node {
        T value;
        int height;
        Node* left;
        Node* right;

        Node(const T& value) : value(value), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;


    Node* insert(Node* node, const T& value) {
    if (!node) {
        return new Node(value);
    }

    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    } else {
        return node;
    }

    node->updateHeight();
    node->balance();

    return node;
}