// Header file for AVLTree
// Author: Blake Boswell
#ifndef CLASS_H
#define CLASS_H
// #include "BinarySearchTree.h"
#include <utility>
#include <string>

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

protected:
    AVLNode<Key, T>* root;
    AVLNode<Key, T>* getLargest(AVLNode<Key, T>* node);
    AVLNode<Key, T>* getSmallest(AVLNode<Key, T>* node);

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