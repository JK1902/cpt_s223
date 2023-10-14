#ifndef AVLNODE_HPP
#define AVLNODE_HPP

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class AVLNode {
public:
    T value;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const T& value) : value(value), height(1), left(nullptr), right(nullptr) {}

    ~AVLNode() {
        delete left;
        delete right;
    }

    int balanceFactor() const {
        return height(left) - height(right);
    }

    void updateHeight() {
        height = 1 + std::max(height(left), height(right));
    }

    void rotateRight() {
        AVLNode* newRoot = left;
        left = newRoot->right;
        newRoot->right = this;
        updateHeight();
        newRoot->updateHeight();
        this = newRoot;
    }

    void rotateLeft() {
        AVLNode* newRoot = right;
        right = newRoot->left;
        newRoot->left = this;
        updateHeight();
        newRoot->updateHeight();
        this = newRoot;
    }

    void balance() {
        updateHeight();
        if (balanceFactor() > 1) {
            if (height(left->left) >= height(left->right)) {
                rotateRight();
            } else {
                left->rotateLeft();
                rotateRight();
            }
        } else if (balanceFactor() < -1) {
            if (height(right->right) >= height(right->left)) {
                rotateLeft();
            } else {
                right->rotateRight();
                rotateLeft();
            }
        }
    }

private:
    int height(AVLNode* node) const {
        return node ? node->height : -1;
    }
};

#endif 