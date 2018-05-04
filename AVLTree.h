// Header file for AVLTree
// Author: Blake Boswell
#ifndef CLASS_H
#define CLASS_H
// #include "BinarySearchTree.h"
#include <utility>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename Key, typename T>
struct AVLNode {
    typedef pair<Key, T> value_type;
    int balanceFactor;
    value_type data;
    
    AVLNode<Key, T>* left;
    AVLNode<Key, T>* right;

    static void copyNode(AVLNode<Key, T>* &thisNode, AVLNode<Key, T>* &sourceNode) {
        if(sourceNode == NULL) {
            thisNode = NULL;
        } else {
            thisNode = new AVLNode<Key, T>;
            thisNode->data = sourceNode->data;
            thisNode->balanceFactor = sourceNode->balanceFactor;
            copyNode(thisNode->left, sourceNode->left);
            copyNode(thisNode->right, sourceNode->right);
        }
    }
};

// struct AVLNode<Key, T>;
template <typename Key, typename T>
class AVLTree {
    typedef pair<Key, T> value_type;
    typedef pair<Key, T>& reference;
    typedef pair<Key, T>* pointer;
    typedef AVLNode<Key, T> Node;
public:
    
    AVLTree();
    AVLTree(AVLTree<Key, T>* tree);
    ~AVLTree();
    bool search(Key key);
    bool insert(value_type data);
    bool remove(Key key);
    void show();
    int height();
    int size();
    bool check();
    // Post-fix ++
    AVLTree<Key, T> operator++(int) {
        cout << "Position before: " << get<0>(position) << endl;
        // data++;
        AVLTree iterator = *this;
        if(position->right != NULL && position->left != NULL) {
            position = getSmallest(position->right);
        } else if(position->left != NULL) {
            position = searchParent(root);
        } else if(position->right != NULL) {
            position = getSmallest(position->right);
        } else if(position->right == NULL && position->left == NULL) {
            // no children
            // search and save every time you go left
            position = searchSuccessor(root);
        }
        cout << "Position after: " << get<0>(position) << endl;
        return iterator;
    }
    reference operator*() {
        return position;
    }
    bool operator==(const AVLTree<Key, T>& rightSide) {
        return position == rightSide.position;
    }
    void set(Node* value) {
        this->position = value;
    }
    Node* begin() {
        return this->root;
    }
    void test(value_type testVal) {
        insert(testVal);
    }

protected:
    Node* root;
    Node* position;
    Node* getLargest(Node* node);
    Node* getSmallest(Node* node);
    Node* searchParentHelper(Node* node, Key key);
    Node* searchParent(Node* node);
    Node* searchSuccessorHelper(Node* node, Key key, Node* savedNode);
    Node* searchSuccessor(Node* node);


private:
    void copyTree(AVLNode<Key, T>* &thisRoot, AVLNode<Key, T>* &sourceRoot);
    void insertionRebalance(AVLNode<Key, T>* &node);
    void deletionRebalance(AVLNode<Key, T>* &node);
    bool insertHelper(AVLNode<Key, T>* &node, pair<Key, T> data, bool& flag);
    int calculateHeight(AVLNode<Key, T>* node);
    void showInorder(AVLNode<Key, T>* node);
    void showPostorder(AVLNode<Key, T>* node);
    void rrRotation(AVLNode<Key, T>* &node, bool isInsert);
    void rlRotation(AVLNode<Key, T>* &node, bool isInsert);
    void llRotation(AVLNode<Key, T>* &node, bool isInsert);
    void lrRotation(AVLNode<Key, T>* &node, bool isInsert);
    pair<Key, T> deleteMax(AVLNode<Key, T>* &node);
    void rotate(AVLNode<Key, T>* &node);
    bool searchHelper(AVLNode<Key, T>* node, Key key);
    void removeBoth(AVLNode<Key, T>* node);
    void removeNode(AVLNode<Key, T>* &node, bool& flag);
    bool removeHelper(AVLNode<Key, T>* &node, Key key, bool& flag);
    void calculateBalanceFactors(AVLNode<Key, T>* &node);
    int sizeHelper(AVLNode<Key, T>* node, int &size);
    bool checkHelper(AVLNode<Key, T>* node);


};
#endif