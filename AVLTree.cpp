// Author: Blake Boswell
#include "AVLTree.h"
#include <iostream>
#include <cmath>

using namespace std;

AVLTree::AVLTree(): BinarySearchTree() {
    this->root = NULL;
}

AVLTree::AVLTree(AVLTree* tree) {
    if(tree->root == NULL) {
        this->root = NULL;
    } else {
        copyTree(this->root, tree->root);
    }
}

void AVLTree::copyTree(AVLNode* &thisRoot, AVLNode* &sourceRoot) {
    if(sourceRoot == NULL) {
        thisRoot = NULL;
    } else {
        thisRoot = new AVLNode;
        thisRoot->data = sourceRoot->data;
        thisRoot->balanceFactor = sourceRoot->balanceFactor;
        copyTree(thisRoot->left, sourceRoot->left);
        copyTree(thisRoot->right, sourceRoot->right);
    }
}

AVLTree::~AVLTree() {
    delete root;
}

void AVLTree::rrRotation(AVLNode* &node, bool isInsert) {
   // cout << "RR ROT on " << node->data << endl;
    AVLNode* oldRoot = node;
    node = oldRoot->right;
    AVLNode* tempLeft = node->left;
    node->left = oldRoot;
    node->left->right = tempLeft;

    // Fix balance factors
    if(isInsert) {
        node->balanceFactor = 0;
        node->left->balanceFactor = 0;
        // +1 to parent
        // Below for deletion
    } else if(node->balanceFactor == -1) {
        node->balanceFactor = 0;
        oldRoot->balanceFactor = 0;
        // -1 up
    } else if(node->balanceFactor == 0) {
        node->balanceFactor = 1;
        oldRoot->balanceFactor = -1;
        // Nothing up
    }
    
}

void AVLTree::rlRotation(AVLNode* &node, bool isInsert) {
    // cout << "RL ROT on " << node->data << endl;
    int oldRLBalanceFactor = node->right->left->balanceFactor;
    AVLNode* temp = node;
    node = node->right->left;
    AVLNode* tempLeft = node->left;
    node->left = temp;
    AVLNode* tempRight = node->right;
    node->right = temp->right;
    temp->right = tempLeft;
    node->right->left = tempRight;

    // Fix balance factors
    if(isInsert) {
        node->balanceFactor = 0;
        if(oldRLBalanceFactor == -1) {
            node->left->balanceFactor = 1;
        } else {
            node->left->balanceFactor = 0;
        }

        if(oldRLBalanceFactor == 1) {
            node->right->balanceFactor = -1;
        } else {
            node->right->balanceFactor = 0;
        }
        // +1 to parent
        // Below for deletion
    } else if(node->right->balanceFactor == 1 && oldRLBalanceFactor == 1) {
        node->balanceFactor = 0;
        node->right->balanceFactor = -1;
        node->left->balanceFactor = 0;
        // -1 up
    } else if(node->right->balanceFactor == 1 && oldRLBalanceFactor == 0) {
        node->balanceFactor = 0;
        node->right->balanceFactor = 0;
        node->left->balanceFactor = 0;
    } else if(node->right->balanceFactor == 1 && oldRLBalanceFactor == -1) {
        node->balanceFactor = 0;
        node->right->balanceFactor = 0;
        node->left->balanceFactor = 1;
    }

}

void AVLTree::llRotation(AVLNode* &node, bool isInsert) {
    // cout << "LL ROT on " << node->data << endl;
    int oldLLBalanceFactor = node->left->left->balanceFactor;
    AVLNode* oldRoot = node;
    node = node->left;
    AVLNode* tempRight = node->right;
    node->right = oldRoot;
    node->right->left = tempRight;

    // Fix balance factors
    if(isInsert) {
        node->balanceFactor = 0;
        node->right->balanceFactor = 0;
        // -1 to parent
        // Below for deletion
    } else if(node->balanceFactor == -1) {
        cout << "This should never happen!" << endl;
            // node->balanceFactor = 0;
            // node->right->balanceFactor = 0;
            // Continue up
        
    } else if(node->balanceFactor == 0) {
            node->balanceFactor = -1;
            node->right->balanceFactor = 1;
            // Nothing up
    } else if(node->balanceFactor == 1) {
        node->balanceFactor = 0;
        node->right->balanceFactor = 0;
    }
    
}

void AVLTree::lrRotation(AVLNode* &node, bool isInsert) {
    // Pull up new root to this subtree
    // cout << "LR ROT on " << node->data << endl;
    int oldLRBalanceFactor = node->left->right->balanceFactor;
    AVLNode* temp;
    temp = node;
    node = temp->left->right;
    AVLNode* tempRight = node->right;
    node->right = temp;
    node->right->left->right = node->left;
    temp = node->right->left;
    node->right->left = tempRight;
    node->left = temp;

    // Fix balance factors
    if(isInsert) {
        node->balanceFactor = 0;
        if(oldLRBalanceFactor == 1) {
            node->left->balanceFactor = 0;
            node->right->balanceFactor = -1;
        } else if(oldLRBalanceFactor == -1) {
            node->left->balanceFactor = 1;
            node->right->balanceFactor = 0;
        } else {
            node->balanceFactor = 0;
            node->left->balanceFactor = 0;
            node->right->balanceFactor = 0;
        }
        // -1 to parent
        // Below for deletion
    } else if(node->left->balanceFactor == -1) {
        if(node->balanceFactor == -1) {
            node->balanceFactor = 0;
            node->left->balanceFactor = 1;
            node->right->balanceFactor = 0;
        } else if(node->balanceFactor == 0) {
            node->left->balanceFactor = 0;
            node->right->balanceFactor = 0;
        } else if(node->balanceFactor == 1) {
            node->balanceFactor = 0;
            node->left->balanceFactor = 0;
            node->right->balanceFactor = -1;
        }
    }
    
    
    
    
}

// Purpose: Determine what rotation to perform
void AVLTree::rotate(AVLNode* &node) {

}

bool AVLTree::searchHelper(AVLNode* node, int key) {
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

// Purpose: Find the data in the tree given a key
bool AVLTree::search(int key) {
    return searchHelper(this->root, key);
}

void AVLTree::insertionRebalance(AVLNode* &node) {
    if(node == NULL) {
        return;
    }
    calculateBalanceFactors(node);
    insertionRebalance(node->left);
    insertionRebalance(node->right);
}

/**
 * Helper method for a recursive insert into the tree
 * flag: the height of the subtree inserted into has increased by one
*/
bool AVLTree::insertHelper(AVLNode* &node, int key, bool& flag) {
    if(node == NULL) {
        node = new AVLNode;
        node->data = key;
        node->left = NULL;
        node->right = NULL;
        node->balanceFactor = 0;
        flag = true;
        return true;
    }
    if(node->data == key) {
        // Data already exists
        flag = false;
        return false;
    }
    if(node->data > key) {
        // Go down the left subtree
        bool didInsert = insertHelper(node->left, key, flag);
        if(didInsert && flag) {
            // height has increased by one from this insertion on left subtree
            node->balanceFactor += 1;
            if(node->balanceFactor >= 2) {
                // Rotate L*
                if(node->left->balanceFactor < 0) {
                    lrRotation(node, true);
                    flag = false;
                } else if(node->left->balanceFactor > 0) {
                    llRotation(node, true);
                    flag = false;
                }
            }
            if(node->balanceFactor == 0) {
                flag = false;
            }
        }
        return didInsert;
    } else {
        // Go down the right subtree
        bool didInsert = insertHelper(node->right, key, flag);
        if(didInsert && flag) {
            node->balanceFactor -= 1;
            if(node->balanceFactor <= -2) {
                if(node->right->balanceFactor < 0) {
                    rrRotation(node, true);
                    flag = true;
                } else if(node->right->balanceFactor > 0) {
                    rlRotation(node, true);
                    flag = true;
                }
            }
            if(node->balanceFactor == 0) {
                flag = false;
            }
        }
        return didInsert;
    }
}

// Purpose: Insert into the tree and balance it
bool AVLTree::insert(int key) {
    bool flag = true;
    return insertHelper(this->root, key, flag);

}

AVLNode* getLargest(AVLNode* node) {
    if(node == NULL) {
        return NULL;
    }
    if(node->right != NULL) {
        return getLargest(node->right);
    } else {
        return node;
    }
}

int AVLTree::deleteMax(AVLNode* &node) {
    AVLNode* predecessor = getLargest(node);
    int data = predecessor->data;
    bool flag = true;
    removeHelper(this->root, data, flag);
    return data;
}

/**
 * Remove a node that has 2 children
 * @param root
 */
void AVLTree::removeBoth(AVLNode* node) {
    // cout << node->balanceFactor << endl;
    int newValue = deleteMax(node->left);
    node->data = newValue;
    // cout << node->balanceFactor << endl;
    
}

/**
 * Remove a node that has only 1 child
 * @param root
 */
void AVLTree::removeNode(AVLNode* & node, bool& flag) {
    if(node->left == NULL && node->right == NULL) {
        // Leaf node
        // cout << "[Leaf RM] Removing " << node->data << endl;
        delete node;
        node = NULL;
        
    } else if(node->left == NULL) {
        // Single child on the right
        // cout << "[Has right] Removing " << node->data << endl;
        AVLNode* temp = node;
        node = node->right;
        delete temp;
    } else if(node->right == NULL) {
        // Single child on the left
        // cout << "[Has left] Removing " << node->data << endl;
        AVLNode* temp = node;
        node = node->left;
        delete temp;
    } else {
        // cout << "[Has both] Removing " << node->data << endl;
        removeBoth(node);
        flag = false;
    }
}
/**
 * Decide how we are going to remove a node, and deal with the BF changes
 * flag: the height of the subtree deleted from has decreased by one
*/
bool AVLTree::removeHelper(AVLNode* &node, int key, bool& flag) {
    if(node == NULL) {
        return false;
    }
    if(node->data == key) {
        flag = true;
        removeNode(node, flag);
        return true;
    } else if(node->data > key) {
        bool didRemove = removeHelper(node->left, key, flag);
        if(didRemove && flag) {
            node->balanceFactor -= 1;
            if(node->balanceFactor == 0) {
                // Remove one up the tree
                flag = true;
            } else if(node->balanceFactor == -1) {
                // Don't change up the tree
                flag = false;
            } else if(node->balanceFactor <= -2) {
                
                if(node->right->balanceFactor == -1) {
                    rrRotation(node, false);
                    flag = true;
                } else if(node->right->balanceFactor == 0) {
                    rrRotation(node, false);
                    flag = false;
                } else if(node->right->balanceFactor == 1) {
                    rlRotation(node, false);
                    flag = true;
                }
            }
        }
        
        return didRemove;
    } else if(node->data < key) {
        bool didRemove = removeHelper(node->right, key, flag);
        if(didRemove && flag) {
            node->balanceFactor += 1;
            if(node->balanceFactor == 0) {
                flag = true;
            } else if(node->balanceFactor == 1) {
                flag = false;
            } else if(node->balanceFactor >= 2) {
               
                if(node->left->balanceFactor == -1) {
                    lrRotation(node, false);
                    flag = true;
                } else if(node->left->balanceFactor == 0) {
                    llRotation(node, false);
                    flag = false;
                }else if(node->left->balanceFactor == 1) {
                    llRotation(node, false);
                    flag = true;
                }
            }
        }
        return didRemove;
    }
    return false;
}

// Purpose: Remove from the tree and balance it
bool AVLTree::remove(int key) {
    bool flag = true;
    return removeHelper(this->root, key, flag);
}

void AVLTree::calculateBalanceFactors(AVLNode* &node) {
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    node->balanceFactor = leftHeight - rightHeight;
}

/**
 * Prints the tree in Inorder
 */
void AVLTree::showInorder(AVLNode* node) {
    if(node == NULL) {
        return;
    }
    showInorder(node->left);
    cout << "[" << node->data << "] :: " << node->balanceFactor << ", ";
    showInorder(node->right);

}

/**
 * Prints the tree in Postorder
 */
void AVLTree::showPostorder(AVLNode* node) {
    if(node == NULL) {
        return;
    }
    showPostorder(node->left);
    showPostorder(node->right);
    cout << "[" << node->data << "] :: " << node->balanceFactor << ", ";
}

// Purpose: Show the contents of the tree
void AVLTree::show() {
    cout << "Inorder:\n";
    this->showInorder(this->root);
    cout << "\nPostOrder:\n";
    this->showPostorder(this->root);
    cout << "\n";
}

int AVLTree::calculateHeight(AVLNode* node) { 
    if(node == NULL) {
        return 0;
    }
    return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
}

// Purpose: Retrieve the height of the tree
int AVLTree::height() {
    return calculateHeight(this->root);
}

int AVLTree::sizeHelper(AVLNode* node, int &size) {
    if(node == NULL) {
        return size;
    }
    size++;
    sizeHelper(node->left, size);
    sizeHelper(node->right, size);
    return size;
}

// Purpose: Retrieve the number of nodes in the tree
int AVLTree::size() {
    int size = 0;
    return sizeHelper(this->root, size);
}

bool AVLTree::checkHelper(AVLNode* node) {
    if(node == NULL) {
        return true;
    }
    if(node->left == NULL && node->right != NULL) {
        bool isBST = (node->data < node->right->data);
        bool isAVL = (abs(calculateHeight(node->left) - calculateHeight(node->right)) <= 1);
        return (isBST && isAVL);

    }
    if(node->left != NULL && node->right == NULL) {
        bool isBST = (node->data > node->left->data);
        bool isAVL = (abs(calculateHeight(node->left) - calculateHeight(node->right)) <= 1);
        return (isBST && isAVL);
    }
    if(checkHelper(node->left) == false || checkHelper(node->right) == false) {
        return false;
    } else {
        return true;
    }
}

// Purpose: Check to see if this tree is an AVL tree
bool AVLTree::check() {
    return checkHelper(this->root);
}