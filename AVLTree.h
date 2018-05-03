// Header file for AVLTree
// Author: Blake Boswell
#include "BinarySearchTree.h"

struct AVLNode: Node {
    int balanceFactor;
    AVLNode* left;
    AVLNode* right;

    static void copyNode(AVLNode* &thisNode, AVLNode* &sourceNode) {
        if(sourceNode == NULL) {
            thisNode = NULL;
        } else {
            thisNode = new AVLNode;
            thisNode->data = sourceNode->data;
            thisNode->balanceFactor = sourceNode->balanceFactor;
            copyNode(thisNode->left, sourceNode->left);
            copyNode(thisNode->right, sourceNode->right);
        }
    }
};

class AVLTree: public BinarySearchTree {
private:
    AVLNode* root;
    void copyTree(AVLNode* &thisRoot, AVLNode* &sourceRoot);
    void insertionRebalance(AVLNode* &node);
    void deletionRebalance(AVLNode* &node);
    bool insertHelper(AVLNode* &node, int key, bool& flag);
    int calculateHeight(AVLNode* node);
    void showInorder(AVLNode* node);
    void showPostorder(AVLNode* node);
    void rrRotation(AVLNode* &node, bool isInsert);
    void rlRotation(AVLNode* &node, bool isInsert);
    void llRotation(AVLNode* &node, bool isInsert);
    void lrRotation(AVLNode* &node, bool isInsert);
    int deleteMax(AVLNode* &node);
    void rotate(AVLNode* &node);
    bool searchHelper(AVLNode* node, int key);
    void removeBoth(AVLNode* node);
    void removeNode(AVLNode* &node, bool& flag);
    bool removeHelper(AVLNode* &node, int key, bool& flag);
    void calculateBalanceFactors(AVLNode* &node);
    int sizeHelper(AVLNode* node, int &size);
    bool checkHelper(AVLNode* node);

public:
    AVLTree();
    AVLTree(AVLTree* tree);
    ~AVLTree();
    bool search(int key);
    bool insert(int key);
    bool remove(int key);
    void show();
    int height();
    int size();
    bool check();
};