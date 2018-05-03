//
// Created by blake on 3/3/2018.
// Implementation of the BinarySearchTree using recursive functions
//
#include "BinarySearchTree.h"
#include <iostream>

using namespace std;

BinarySearchTree::BinarySearchTree() {
    this->node = NULL;
}

BinarySearchTree::~BinarySearchTree() {
    delete node;
}

Node* BinarySearchTree::searchHelper(Node* node, int key) {
    if(node == NULL) {
        // Tree is empty
        return NULL;
    }
    if(node->data == key) {
        // Found the node
        return node;
    }
    if(node->data > key) {
        // Go down the left subtree
        return searchHelper(node->left, key);
    } else {
        // Go down the right subtree
        return searchHelper(node->right, key);
    }
}

/**
 * Returns the node with data equal to the given key
 * @param key
 * @return BinarySearchTree
 */
Node* BinarySearchTree::search(int key) {
    return searchHelper(this->node, key);
}

bool BinarySearchTree::insertHelper(Node* &node, int key) {
    if(node == NULL) {
        node = new Node;
        node->data = key;
        node->left = NULL;
        node->right = NULL;
        return true;
    }
    if(node->data == key) {
        // Data already exists
        return false;
    }
    if(node->data > key) {
        // Go down the left subtree
        return insertHelper(node->left, key);
    } else {
        // Go down the right subtree
        return insertHelper(node->right, key);
    }
}

/**
 * Inserts a new node into the tree with data equal to the key
 * @param root
 * @param key
 * @return True if successful, False otherwise
 */
bool BinarySearchTree::insert(int key) {
    return insertHelper(this->node, key);
}

/**
 * Remove a node that has 2 children
 * @param root
 */
void BinarySearchTree::removeBoth(Node* &node) {
    Node* temp = node;
    node = node->right;
    node->left = temp->left;
    delete temp;
}

/**
 * Remove a node that has only 1 child
 * @param root
 */
void BinarySearchTree::removeNode(Node* & node) {
    if(node->left == NULL && node->right == NULL) {
        // Leaf node
        delete node;
        node = NULL;
    } else if(node->left == NULL) {
        // Single child on the right
        Node* temp = node;
        node = node->right;
        delete temp;
    } else if(node->right == NULL) {
        // Single child on the left
        Node* temp = node;
        node = node->left;
        delete temp;
    } else {
        removeBoth(node);
    }
}

bool BinarySearchTree::removeHelper(Node* &node, int key) {
    if(node == NULL) {
        return false;
    }
    if(node->data == key) {
        removeNode(node);
    } else if(node->data > key) {
        return removeHelper(node->left, key);
    } else if(node->data < key) {
        return removeHelper(node->right, key);
    }
}

/**
 * Remove a node with data equal to the given key
 * @param root
 * @param key
 * @return True if successful, False otherwise
 */
bool BinarySearchTree::remove(int key) {
    return removeHelper(this->node, key);
}

/**
 * Prints the tree in Inorder
 */
void BinarySearchTree::showInorder(Node* node) {
    if(node == NULL) {
        return;
    }
    showInorder(node->left);
    cout << node->data << ", ";
    showInorder(node->right);

}

/**
 * Prints the tree in Postorder
 */
void BinarySearchTree::showPostorder(Node* node) {
    if(node == NULL) {
        return;
    }
    showPostorder(node->left);
    showPostorder(node->right);
    cout << node->data << ", ";
}

/**
 * Print out both the Inorder and Postorder of the tree
 */
void BinarySearchTree::show() {
    cout << "Inorder:\n";
    this->showInorder(this->node);
    cout << "\nPostOrder:\n";
    this->showPostorder(this->node);
    cout << "\n";
}

int BinarySearchTree::calculateHeight(Node* node) {
    if(node == NULL) {
        return 0;
    }
    return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
}

/**
 * Finds the height of the tree
 * @return height
 */
int BinarySearchTree::height() {
    return calculateHeight(this->node);
}

/**
 * Helper function to size
 * @param size
 * @return size
 */
int BinarySearchTree::sizeHelper(Node* node, int &size) {
    if(node == NULL) {
        return size;
    }
    size++;
    sizeHelper(node->left, size);
    sizeHelper(node->right, size);
    return size;
}

/**
 * Finds the total number of nodes in the tree
 * @return size
 */
int BinarySearchTree::size() {
    int size = 0;
    return sizeHelper(this->node, size);
}

bool BinarySearchTree::checkHelper(Node* node) {
    if(node == NULL) {
        return true;
    }
    if(node->left == NULL && node->right != NULL) {
        return (node->data < node->right->data);
    }
    if(node->left != NULL && node->right == NULL) {
        return (node->data > node->left->data);
    }
    if(checkHelper(node->left) == false || checkHelper(node->right) == false) {
        return false;
    } else {
        return true;
    }
}

/**
 * Checks that the tree is a Binary Search Tree
 * left data < node data < right data
 * @return T/F
 */
bool BinarySearchTree::check() {
    return checkHelper(this->node);
}

/**
 * Function for debugging the check function
 * @param data
 */
void BinarySearchTree::setData(int data) {
    this->node->data = data;
}

