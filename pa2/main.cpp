cpp
#include <iostream>
#include "AVLTree.hpp"

int main() {
    AVLTree<int> tree;

    // Insert data into the tree
    for (int i = 1; i <= 100; i += 2) {
        tree.insert(i);
    }

    // Print the height of the tree
    std::cout << "Height of the tree: " << tree.height() << std::endl;

    // Print the result of validate() function
    std::cout << "Is the tree valid: " << (tree.validate() ? "Yes" : "No") << std::endl;

    // Check if the tree contains odd numbers between 1 and 100
    for (int i = 1; i <= 100; i++) {
        if (tree.contains(i) != (i % 2 == 1)) {
            std::cout << "My AVLTree implementation is wrong" << std::endl;
            break;
        }
    }

    return 0;
}