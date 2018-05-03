//
// Created by blake on 3/3/2018.
// Header file for the BinarySearchTree class
//
#include <cstddef>

struct Node {
    Node* left;
    Node* right;
    int data;
};

class BinarySearchTree {
private:
    Node* node;
    Node* searchHelper(Node* node, int key);
    bool insertHelper(Node* &node, int key);
    bool removeHelper(Node* &node, int key);
    int sizeHelper(Node* node, int& size);
    void removeBoth(Node* &node);
    void removeNode(Node* &node);
    void showInorder(Node* node);
    void showPostorder(Node* node);
    int calculateHeight(Node* node);
    bool checkHelper(Node* node);

public:
    explicit BinarySearchTree();
    ~BinarySearchTree();
    Node* search(int key);
    bool insert(int key);
    bool remove(int key);
    void show();
    int height();
    int size();
    bool check();

    // For debugging only
    void setData(int data);
};
