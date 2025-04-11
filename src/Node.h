#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node{ // Node structure
    T data;
    Node<T>* next;

    // Constructor with data and next null pointer
    Node(T d) : data(d), next(NULL) {}
};

#endif