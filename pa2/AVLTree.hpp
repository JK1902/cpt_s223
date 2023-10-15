#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.hpp"

template<typename T>
class AVLTree {

private:
    AVLNode<T>* root;

public:
    // Constructors
    AVLTree() : root(nullptr) {}
    ~AVLTree() {
        clear(root);
    }

    // Public member functions
    int height() {
        return heightHelper(root);
    }

    void insert(const T& value) {
        root = insertHelper(root, value);
    }

    bool contains(const T& value) {
        return containsHelper(root, value);
    }

    bool validate() {
        return validateHelper(root);
    }

private:
    // Private helper functions
    int heightHelper(AVLNode<T>* node) {
        if (node == nullptr) return -1;
        return node->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getBalance(AVLNode<T>* node) {
        if (node == nullptr) return 0;
        return heightHelper(node->left) - heightHelper(node->right);
    }

    private:
    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* temp = x->right;

        x->right = y;
        y->left = temp;

        y->height = max(heightHelper(y->left), heightHelper(y->right)) + 1;
        x->height = max(heightHelper(x->left), heightHelper(x->right)) + 1;

        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = max(heightHelper(x->left), heightHelper(x->right)) + 1;
        y->height = max(heightHelper(y->left), heightHelper(y->right)) + 1;

        return y;
    }
    

    AVLNode<T>* insertHelper(AVLNode<T>* node, const T& value) {
        if (node == nullptr) {
            return new AVLNode<T>(value);
        }

        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        } else {
            return node; // Duplicate values are not allowed
        }

        node->height = 1 + max(heightHelper(node->left), heightHelper(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    bool containsHelper(AVLNode<T>* node, const T& value) {
        if (node == nullptr) {
            return false;
        }

        if (value == node->data) {
            return true;
        }

        if (value < node->data) {
            return containsHelper(node->left, value);
        } else {
            return containsHelper(node->right, value);
        }
    }

    bool validateHelper(AVLNode<T>* node) {
        if (node == nullptr) {
            return true;
        }

        int balance = getBalance(node);

        if (balance > 1 || balance < -1) {
            return false;
        }

        return validateHelper(node->left) && validateHelper(node->right);
    }

    void clear(AVLNode<T>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

#endif 
