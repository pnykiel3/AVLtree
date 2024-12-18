// AVLTree.h
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

// Node structure
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(int key);
    void remove(int key);
    bool search(int key) const;
    void printInOrder() const;

private:
    Node* root;

    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);
    Node* search(Node* node, int key) const;
    void printInOrder(Node* node) const;
    void deleteTree(Node* node);

    int getHeight(Node* node) const;
    int getBalanceFactor(Node* node) const;
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
};

#endif // AVLTREE_H
