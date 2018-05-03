// Author: Blake Boswell
#include "AVLTree.h"
#include <iostream>
#include <cmath>

using namespace std;

template<typename Key, typename T>
AVLTree<Key, T>::AVLTree() {
    this->root = NULL;
}

template<typename Key, typename T>
AVLTree<Key, T>::AVLTree(AVLTree<Key, T>* tree) {
    if(tree->root == NULL) {
        this->root = NULL;
    } else {
        copyTree(this->root, tree->root);
    }
}

template<typename Key, typename T>
void AVLTree<Key, T>::copyTree(AVLNode<Key, T>* &thisRoot, AVLNode<Key, T>* &sourceRoot) {
    if(sourceRoot == NULL) {
        thisRoot = NULL;
    } else {
        thisRoot = new AVLNode<Key, T>;
        thisRoot->data = sourceRoot->data;
        thisRoot->balanceFactor = sourceRoot->balanceFactor;
        copyTree(thisRoot->left, sourceRoot->left);
        copyTree(thisRoot->right, sourceRoot->right);
    }
}

template<typename Key, typename T>
AVLTree<Key, T>::~AVLTree() {
    delete root;
}

template<typename Key, typename T>
void AVLTree<Key, T>::rrRotation(AVLNode<Key, T>* &node, bool isInsert) {
   // cout << "RR ROT on " << node->data << endl;
    AVLNode<Key, T>* oldRoot = node;
    node = oldRoot->right;
    AVLNode<Key, T>* tempLeft = node->left;
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

template<typename Key, typename T>
void AVLTree<Key, T>::rlRotation(AVLNode<Key, T>* &node, bool isInsert) {
    // cout << "RL ROT on " << node->data << endl;
    int oldRLBalanceFactor = node->right->left->balanceFactor;
    AVLNode<Key, T>* temp = node;
    node = node->right->left;
    AVLNode<Key, T>* tempLeft = node->left;
    node->left = temp;
    AVLNode<Key, T>* tempRight = node->right;
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

template<typename Key, typename T>
void AVLTree<Key, T>::llRotation(AVLNode<Key, T>* &node, bool isInsert) {
    // cout << "LL ROT on " << node->data << endl;
    int oldLLBalanceFactor = node->left->left->balanceFactor;
    AVLNode<Key, T>* oldRoot = node;
    node = node->left;
    AVLNode<Key, T>* tempRight = node->right;
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

template<typename Key, typename T>
void AVLTree<Key, T>::lrRotation(AVLNode<Key, T>* &node, bool isInsert) {
    // Pull up new root to this subtree
    // cout << "LR ROT on " << node->data << endl;
    int oldLRBalanceFactor = node->left->right->balanceFactor;
    AVLNode<Key, T>* temp;
    temp = node;
    node = temp->left->right;
    AVLNode<Key, T>* tempRight = node->right;
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
template<typename Key, typename T>
void AVLTree<Key, T>::rotate(AVLNode<Key, T>* &node) {

}

template<typename Key, typename T>
bool AVLTree<Key, T>::searchHelper(AVLNode<Key, T>* node, Key key) {
    if(node == NULL) {
        // Tree is empty
        return NULL;
    }
    if(get<0>(node->data) == key) {
        // Found the node
        cout << "Key: " << get<0>(node->data) << "\nValue: " << get<1>(node->data) << endl;
        return node;
    }
    if(get<0>(node->data) > key) {
        // Go down the left subtree
        return searchHelper(node->left, key);
    } else {
        // Go down the right subtree
        return searchHelper(node->right, key);
    }
}

// Purpose: Find the data in the tree given a key
template<typename Key, typename T>
bool AVLTree<Key, T>::search(Key key) {
    return searchHelper(this->root, key);
}

template<typename Key, typename T>
void AVLTree<Key, T>::insertionRebalance(AVLNode<Key, T>* &node) {
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
template<typename Key, typename T>
bool AVLTree<Key, T>::insertHelper(AVLNode<Key, T>* &node, pair<Key, T> data, bool& flag) {
    if(node == NULL) {
        node = new AVLNode<Key, T>;
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        node->balanceFactor = 0;
        flag = true;
        return true;
    }
    if(get<0>(node->data) == get<0>(data)) {
        // Data already exists
        flag = false;
        return false;
    }
    if(get<0>(node->data) > get<0>(data)) {
        // Go down the left subtree
        bool didInsert = insertHelper(node->left, data, flag);
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
        bool didInsert = insertHelper(node->right, data, flag);
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
template<typename Key, typename T>
bool AVLTree<Key, T>::insert(pair<Key, T> data) {
    bool flag = true;
    return insertHelper(this->root, data, flag);

}

template<typename Key, typename T>
AVLNode<Key, T>* AVLTree<Key, T>::getLargest(AVLNode<Key, T>* node) {
    if(node == NULL) {
        return NULL;
    }
    if(node->right != NULL) {
        return getLargest(node->right);
    } else {
        return node;
    }
}

template<typename Key, typename T>
pair<Key, T> AVLTree<Key, T>::deleteMax(AVLNode<Key, T>* &node) {
    AVLNode<Key, T>* predecessor = getLargest(node);
    pair<Key, T> data = predecessor->data;
    bool flag = true;
    removeHelper(this->root, get<0>(data), flag);
    return data;
}

/**
 * Remove a node that has 2 children
 * @param root
 */
template<typename Key, typename T>
void AVLTree<Key, T>::removeBoth(AVLNode<Key, T>* node) {
    // cout << node->balanceFactor << endl;
    pair<Key, T> newValue = deleteMax(node->left);
    node->data = newValue;
    // cout << node->balanceFactor << endl;
    
}

/**
 * Remove a node that has only 1 child
 * @param root
 */
template<typename Key, typename T>
void AVLTree<Key, T>::removeNode(AVLNode<Key, T>* & node, bool& flag) {
    if(node->left == NULL && node->right == NULL) {
        // Leaf node
        // cout << "[Leaf RM] Removing " << node->data << endl;
        delete node;
        node = NULL;
        
    } else if(node->left == NULL) {
        // Single child on the right
        // cout << "[Has right] Removing " << node->data << endl;
        AVLNode<Key, T>* temp = node;
        node = node->right;
        delete temp;
    } else if(node->right == NULL) {
        // Single child on the left
        // cout << "[Has left] Removing " << node->data << endl;
        AVLNode<Key, T>* temp = node;
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
template<typename Key, typename T>
bool AVLTree<Key, T>::removeHelper(AVLNode<Key, T>* &node, Key key, bool& flag) {
    if(node == NULL) {
        return false;
    }
    if(get<0>(node->data) == key) {
        flag = true;
        removeNode(node, flag);
        return true;
    } else if(get<0>(node->data) > key) {
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
    } else if(get<0>(node->data) < key) {
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
template<typename Key, typename T>
bool AVLTree<Key, T>::remove(Key key) {
    bool flag = true;
    return removeHelper(this->root, key, flag);
}

template<typename Key, typename T>
void AVLTree<Key, T>::calculateBalanceFactors(AVLNode<Key, T>* &node) {
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    node->balanceFactor = leftHeight - rightHeight;
}

/**
 * Prints the tree in Inorder
 */
template<typename Key, typename T>
void AVLTree<Key, T>::showInorder(AVLNode<Key, T>* node) {
    if(node == NULL) {
        return;
    }
    showInorder(node->left);
    cout << "[" << get<0>(node->data) << ": " << get<1>(node->data) << "] :: " << node->balanceFactor << ", ";
    showInorder(node->right);

}

/**
 * Prints the tree in Postorder
 */
template<typename Key, typename T>
void AVLTree<Key, T>::showPostorder(AVLNode<Key, T>* node) {
    if(node == NULL) {
        return;
    }
    showPostorder(node->left);
    showPostorder(node->right);
    cout << "[" << get<0>(node->data) << ": " << get<1>(node->data) << "] :: " << node->balanceFactor << ", ";
}

// Purpose: Show the contents of the tree
template<typename Key, typename T>
void AVLTree<Key, T>::show() {
    cout << "Inorder:\n";
    this->showInorder(this->root);
    cout << "\nPostOrder:\n";
    this->showPostorder(this->root);
    cout << "\n";
}

template<typename Key, typename T>
int AVLTree<Key, T>::calculateHeight(AVLNode<Key, T>* node) { 
    if(node == NULL) {
        return 0;
    }
    return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
}

// Purpose: Retrieve the height of the tree
template<typename Key, typename T>
int AVLTree<Key, T>::height() {
    return calculateHeight(this->root);
}

template<typename Key, typename T>
int AVLTree<Key, T>::sizeHelper(AVLNode<Key, T>* node, int &size) {
    if(node == NULL) {
        return size;
    }
    size++;
    sizeHelper(node->left, size);
    sizeHelper(node->right, size);
    return size;
}

// Purpose: Retrieve the number of nodes in the tree
template<typename Key, typename T>
int AVLTree<Key, T>::size() {
    int size = 0;
    return sizeHelper(this->root, size);
}

template<typename Key, typename T>
bool AVLTree<Key, T>::checkHelper(AVLNode<Key, T>* node) {
    if(node == NULL) {
        return true;
    }
    if(node->left == NULL && node->right != NULL) {
        bool isBST = (get<0>(node->data) < get<0>(node->right->data));
        bool isAVL = (abs(calculateHeight(node->left) - calculateHeight(node->right)) <= 1);
        return (isBST && isAVL);

    }
    if(node->left != NULL && node->right == NULL) {
        bool isBST = (get<0>(node->data) > get<0>(node->left->data));
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
template<typename Key, typename T>
bool AVLTree<Key, T>::check() {
    return checkHelper(this->root);
}


template class AVLTree<int, int>;
template class AVLTree<string, int>;