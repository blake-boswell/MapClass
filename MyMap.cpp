#include "MyMap.h"

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::MyMap(const Compare& comp, const Allocator& alloc) {
    cout << "Default constructor" << endl;
    this->iter = new AVLTree();
}

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::MyMap(const MyMap<Key, T, Compare, Allocator>& x) {
    cout << "Copy constructor" << endl;
}

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::~MyMap() {
     cout << "Destructor" << endl;
}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLTree MyMap<Key, T, Compare, Allocator>::begin() {
    // cout << this->iterator-> << endl;
    iter->set(iter->getRoot());
    return *(this->iter);
}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLTree  MyMap<Key, T, Compare, Allocator>::end() {
    return NULL;
}

template <class Key, class T, class Compare, class Allocator>
bool MyMap<Key, T, Compare, Allocator>::empty() const {
    if(iter->getRoot() == NULL) {
        return true;
    }
    return false;
}

template <class Key, class T, class Compare, class Allocator>
int MyMap<Key, T, Compare, Allocator>::size() const {
    return iter->size();
}

template <class Key, class T, class Compare, class Allocator>
T& MyMap<Key, T, Compare, Allocator>::operator[](const Key& x) {
    cout << "In ere" << endl;
    AVLNode* result = this->iter->search(x);
    cout << "On it" << endl;
    if(result != NULL) {
        cout << result->balanceFactor << endl;
        cout << get<1>(result->data) << endl;
        T value = get<1>(result->data);
        return get<1>(result->data);
    }
    throw out_of_range("That index does not exist");
    
}

template <class Key, class T, class Compare, class Allocator>
pair<typename MyMap<Key, T, Compare, Allocator>::AVLTree, bool> MyMap<Key, T, Compare, Allocator>::insert(const pair<Key, T>& x) {
    cout << "Inserting " << get<0>(x) << ": " << get<1>(x) << endl;
    bool didInsert = this->iter->insert(x);
    
    cout << "Did it make it?? " << didInsert << endl;
    iter->show();
    pair<MyMap<Key, T, Compare, Allocator>::AVLTree, bool> response = make_pair(*(this->iter), didInsert);
    return response;
}

// template <class Key, class T, class Compare, class Allocator>
// unsigned MyMap<Key, T, Compare, Allocator>::erase(const key_type& x) {
//     return 0;
// }

// template <class Key, class T, class Compare, class Allocator>
// void MyMap<Key, T, Compare, Allocator>::clear() {

// }

// template <class Key, class T, class Compare, class Allocator>
// typename MyMap<Key, T, Compare, Allocator>::AVLTree MyMap<Key, T, Compare, Allocator>::find(const Key& x) {
//     return NULL;
// }

// -----------------------------------------------------------------------------------
// -------------------------    AVL Iterator Below  ----------------------------------
// -----------------------------------------------------------------------------------

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::AVLTree::AVLTree() {
    this->root = NULL;
    this->position = NULL;
}

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::AVLTree::AVLTree(MyMap<Key, T, Compare, Allocator>::AVLTree* tree) {
    if(tree->root == NULL) {
        this->root = NULL;
    } else {
        copyTree(this->root, tree->root);
    }
}

template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::copyTree(MyMap<Key, T, Compare, Allocator>::AVLNode* &thisRoot, MyMap<Key, T, Compare, Allocator>::AVLNode* &sourceRoot) {
    if(sourceRoot == NULL) {
        thisRoot = NULL;
    } else {
        thisRoot = new MyMap<Key, T, Compare, Allocator>::AVLNode;
        thisRoot->data = sourceRoot->data;
        thisRoot->balanceFactor = sourceRoot->balanceFactor;
        copyTree(thisRoot->left, sourceRoot->left);
        copyTree(thisRoot->right, sourceRoot->right);
    }
}

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::AVLTree::~AVLTree() {
    delete root;
}

template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::rrRotation(MyMap<Key, T, Compare, Allocator>::AVLNode* &node, bool isInsert) {
   // cout << "RR ROT on " << node->data << endl;
    MyMap<Key, T, Compare, Allocator>::AVLNode* oldRoot = node;
    node = oldRoot->right;
    MyMap<Key, T, Compare, Allocator>::AVLNode* tempLeft = node->left;
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

template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::rlRotation(MyMap<Key, T, Compare, Allocator>::AVLNode* &node, bool isInsert) {
    // cout << "RL ROT on " << node->data << endl;
    int oldRLBalanceFactor = node->right->left->balanceFactor;
    MyMap<Key, T, Compare, Allocator>::AVLNode* temp = node;
    node = node->right->left;
    MyMap<Key, T, Compare, Allocator>::AVLNode* tempLeft = node->left;
    node->left = temp;
    MyMap<Key, T, Compare, Allocator>::AVLNode* tempRight = node->right;
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

template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::llRotation(MyMap<Key, T, Compare, Allocator>::AVLNode* &node, bool isInsert) {
    // cout << "LL ROT on " << node->data << endl;
    int oldLLBalanceFactor = node->left->left->balanceFactor;
    MyMap<Key, T, Compare, Allocator>::AVLNode* oldRoot = node;
    node = node->left;
    MyMap<Key, T, Compare, Allocator>::AVLNode* tempRight = node->right;
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

template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::lrRotation(MyMap<Key, T, Compare, Allocator>::AVLNode* &node, bool isInsert) {
    // Pull up new root to this subtree
    // cout << "LR ROT on " << node->data << endl;
    int oldLRBalanceFactor = node->left->right->balanceFactor;
    MyMap<Key, T, Compare, Allocator>::AVLNode* temp;
    temp = node;
    node = temp->left->right;
    MyMap<Key, T, Compare, Allocator>::AVLNode* tempRight = node->right;
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
template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::rotate(MyMap<Key, T, Compare, Allocator>::AVLNode* &node) {

}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLNode* MyMap<Key, T, Compare, Allocator>::AVLTree::searchHelper(MyMap<Key, T, Compare, Allocator>::AVLNode* node, Key key) {
    if(node == NULL) {
        // Tree is empty
        cout << "Empty tree" << endl;
        return NULL;
    }

    cout << "Looking for Key: " << key << ": " << get<0>(node->data) << endl;
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
template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLNode* MyMap<Key, T, Compare, Allocator>::AVLTree::search(Key key) {
    return searchHelper(this->root, key);
}

template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::insertionRebalance(MyMap<Key, T, Compare, Allocator>::AVLNode* &node) {
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
template <class Key, class T, class Compare, class Allocator>
bool MyMap<Key, T, Compare, Allocator>::AVLTree::insertHelper(MyMap<Key, T, Compare, Allocator>::AVLNode* &node, pair<Key, T> data, bool& flag) {
    if(node == NULL) {
        node = new MyMap<Key, T, Compare, Allocator>::AVLNode;
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
template <class Key, class T, class Compare, class Allocator>
bool MyMap<Key, T, Compare, Allocator>::AVLTree::insert(pair<Key, T> data) {
    bool flag = true;
    return insertHelper(this->root, data, flag);

}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLNode* MyMap<Key, T, Compare, Allocator>::AVLTree::getLargest(MyMap<Key, T, Compare, Allocator>::AVLNode* node) {
    if(node == NULL) {
        return NULL;
    }
    if(node->right != NULL) {
        return getLargest(node->right);
    } else {
        return node;
    }
}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLNode* MyMap<Key, T, Compare, Allocator>::AVLTree::getSmallest(MyMap<Key, T, Compare, Allocator>::AVLNode* node) {
    if(node == NULL) {
        return NULL;
    }
    if(node->left != NULL) {
        return getSmallest(node->left);
    } else {
        return node;
    }
}

template <class Key, class T, class Compare, class Allocator>
pair<Key, T> MyMap<Key, T, Compare, Allocator>::AVLTree::deleteMax(MyMap<Key, T, Compare, Allocator>::AVLNode* &node) {
    MyMap<Key, T, Compare, Allocator>::AVLNode* predecessor = getLargest(node);
    pair<Key, T> data = predecessor->data;
    bool flag = true;
    removeHelper(this->root, get<0>(data), flag);
    return data;
}

/**
 * Remove a node that has 2 children
 * @param root
 */
template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::removeBoth(MyMap<Key, T, Compare, Allocator>::AVLNode* node) {
    // cout << node->balanceFactor << endl;
    pair<Key, T> newValue = deleteMax(node->left);
    node->data = newValue;
    // cout << node->balanceFactor << endl;
    
}

/**
 * Remove a node that has only 1 child
 * @param root
 */
template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::removeNode(MyMap<Key, T, Compare, Allocator>::AVLNode* & node, bool& flag) {
    if(node->left == NULL && node->right == NULL) {
        // Leaf node
        // cout << "[Leaf RM] Removing " << node->data << endl;
        delete node;
        node = NULL;
        
    } else if(node->left == NULL) {
        // Single child on the right
        // cout << "[Has right] Removing " << node->data << endl;
        MyMap<Key, T, Compare, Allocator>::AVLNode* temp = node;
        node = node->right;
        delete temp;
    } else if(node->right == NULL) {
        // Single child on the left
        // cout << "[Has left] Removing " << node->data << endl;
        MyMap<Key, T, Compare, Allocator>::AVLNode* temp = node;
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
template <class Key, class T, class Compare, class Allocator>
bool MyMap<Key, T, Compare, Allocator>::AVLTree::removeHelper(MyMap<Key, T, Compare, Allocator>::AVLNode* &node, Key key, bool& flag) {
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
template <class Key, class T, class Compare, class Allocator>
bool MyMap<Key, T, Compare, Allocator>::AVLTree::remove(Key key) {
    bool flag = true;
    return removeHelper(this->root, key, flag);
}

template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::calculateBalanceFactors(MyMap<Key, T, Compare, Allocator>::AVLNode* &node) {
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    node->balanceFactor = leftHeight - rightHeight;
}

/**
 * Prints the tree in Inorder
 */
template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::showInorder(MyMap<Key, T, Compare, Allocator>::AVLNode* node) {
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
template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::showPostorder(MyMap<Key, T, Compare, Allocator>::AVLNode* node) {
    if(node == NULL) {
        return;
    }
    showPostorder(node->left);
    showPostorder(node->right);
    cout << "[" << get<0>(node->data) << ": " << get<1>(node->data) << "] :: " << node->balanceFactor << ", ";
}

// Purpose: Show the contents of the tree
template <class Key, class T, class Compare, class Allocator>
void MyMap<Key, T, Compare, Allocator>::AVLTree::show() {
    cout << "Inorder:\n";
    this->showInorder(this->root);
    cout << "\nPostOrder:\n";
    this->showPostorder(this->root);
    cout << "\n";
}

template <class Key, class T, class Compare, class Allocator>
int  MyMap<Key, T, Compare, Allocator>::AVLTree::calculateHeight(MyMap<Key, T, Compare, Allocator>::AVLNode* node) { 
    if(node == NULL) {
        return 0;
    }
    return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
}

// Purpose: Retrieve the height of the tree
template <class Key, class T, class Compare, class Allocator>
int  MyMap<Key, T, Compare, Allocator>::AVLTree::height() {
    return calculateHeight(this->root);
}

template <class Key, class T, class Compare, class Allocator>
int MyMap<Key, T, Compare, Allocator>::AVLTree::sizeHelper(MyMap<Key, T, Compare, Allocator>::AVLNode* node, int &size) {
    if(node == NULL) {
        return size;
    }
    size++;
    sizeHelper(node->left, size);
    sizeHelper(node->right, size);
    return size;
}

// Purpose: Retrieve the number of nodes in the tree
template <class Key, class T, class Compare, class Allocator>
int MyMap<Key, T, Compare, Allocator>::AVLTree::size() {
    int size = 0;
    return sizeHelper(this->root, size);
}

template <class Key, class T, class Compare, class Allocator>
bool  MyMap<Key, T, Compare, Allocator>::AVLTree::checkHelper(MyMap<Key, T, Compare, Allocator>::AVLNode* node) {
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
template <class Key, class T, class Compare, class Allocator>
bool  MyMap<Key, T, Compare, Allocator>::AVLTree::check() {
    return checkHelper(this->root);
}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLNode*  MyMap<Key, T, Compare, Allocator>::AVLTree::searchParentHelper(MyMap<Key, T, Compare, Allocator>::AVLNode* node, Key key) {
    if(node == NULL || (node != NULL && get<0>(node->data) == key)) {
        // Tree is empty or this is the root
        return NULL;
    }
    if(node->left != NULL && get<0>(node->left->data) == key || node->right != NULL && get<0>(node->right->data) == key) {
        // Found the node
        cout << "Key: " << get<0>(node->data) << "\nValue: " << get<1>(node->data) << endl;
        return node;
    }
    if(get<0>(node->data) > key) {
        // Go down the left subtree
        return searchParentHelper(node->left, key);
    } else {
        // Go down the right subtree
        return searchParentHelper(node->right, key);
    }
}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLNode* MyMap<Key, T, Compare, Allocator>::AVLTree::searchParent(MyMap<Key, T, Compare, Allocator>::AVLNode* node) {
    return searchParentHelper(node, get<0>(node->data));
}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLNode*  MyMap<Key, T, Compare, Allocator>::AVLTree::searchSuccessorHelper(MyMap<Key, T, Compare, Allocator>::AVLNode* node, Key key, MyMap<Key, T, Compare, Allocator>::AVLNode* savedNode) {
    if(node == NULL) {
        // Tree is empty
        return NULL;
    }
    if(get<0>(node->data) == key) {
        // Found the node
        cout << "Key: " << get<0>(node->data) << "\nValue: " << get<1>(node->data) << endl;
        return savedNode;
    }
    if(get<0>(node->data) > key) {
        // Go down the left subtree
        return searchSuccessorHelper(node->left, key, node);
    } else {
        // Go down the right subtree
        return searchSuccessorHelper(node->right, key, savedNode);
    }
}

template <class Key, class T, class Compare, class Allocator>
typename MyMap<Key, T, Compare, Allocator>::AVLNode*  MyMap<Key, T, Compare, Allocator>::AVLTree::searchSuccessor(MyMap<Key, T, Compare, Allocator>::AVLNode* node) {
    return searchSuccessorHelper(node, get<0>(node->data), node);
}


// template class MyMap<Key, T, Compare, Allocator>::AVLTree<int, int>;
// template class MyMap<Key, T, Compare, Allocator>::AVLTree<string, int>;