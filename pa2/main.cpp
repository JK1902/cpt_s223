#include <iostream>
#include <vector>
#include <algorithm>
#include "AVLTree.hpp"

int main() {
    // Create sequences
    std::vector<int> ascendingSeq, descendingSeq, randomSeq;
    for (int i = 1; i <= 100; i += 2) {
        ascendingSeq.push_back(i);
        descendingSeq.push_back(101 - i);
        randomSeq.push_back(i);
    }
    std::random_shuffle(randomSeq.begin(), randomSeq.end());

    // Create AVL Trees and insert sequences
    AVLTree<int> ascendingTree, descendingTree, randomTree;

    for (int i = 0; i < 50; ++i) {
        ascendingTree.insert(ascendingSeq[i]);
        descendingTree.insert(descendingSeq[i]);
        randomTree.insert(randomSeq[i]);
    }

    // Print heights
    std::cout << "Height of ascendingTree: " << ascendingTree.height() << std::endl;
    std::cout << "Height of descendingTree: " << descendingTree.height() << std::endl;
    std::cout << "Height of randomTree: " << randomTree.height() << std::endl;

    // Validate trees
    std::cout << "ascendingTree is " << (ascendingTree.validate() ? "balanced" : "not balanced") << std::endl;
    std::cout << "descendingTree is " << (descendingTree.validate() ? "balanced" : "not balanced") << std::endl;
    std::cout << "randomTree is " << (randomTree.validate() ? "balanced" : "not balanced") << std::endl;

    // Test contains
    for (int i = 1; i <= 100; ++i) {
        bool isOdd = (i % 2 == 1);
        if (ascendingTree.contains(i) != isOdd ||
            descendingTree.contains(i) != isOdd ||
            randomTree.contains(i) != isOdd) {
            std::cout << "My AVL tree implementation is wrong" << std::endl;
            break;
        }
    }

    return 0;
}
