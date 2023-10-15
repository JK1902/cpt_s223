#ifndef AVLNODE_HPP
#define AVLNODE_HPP

template<typename T>
class AVLNode {
public:
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    // Constructors
    AVLNode() : data(T()), left(nullptr), right(nullptr), height(0) {}
    AVLNode(const T& value) : data(value), left(nullptr), right(nullptr), height(0) {}

    // Destructor
    ~AVLNode() {
        left = nullptr;
        right = nullptr;
    }
};

#endif 
