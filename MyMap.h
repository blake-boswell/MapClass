#include <iostream>
#include <utility>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <stdexcept>
// #include "AVLTree.cpp"
using namespace std;

template <class Key, class T, class Compare = less<Key>, class Allocator = allocator<pair<const Key, T>>>
class MyMap {
    typedef pair<Key, T> value_type;
    typedef int size_type;
    typedef Key key_type;
    
    
    public:
        struct AVLNode {
            typedef pair<Key, T> value_type;
            int balanceFactor;
            value_type data;
            
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

        class AVLTree {
            typedef pair<Key, T> value_type;
            typedef pair<Key, T>& reference;
            typedef pair<Key, T>* pointer;
            typedef AVLNode Node;
            public:
            
                AVLTree();
                AVLTree(AVLTree* tree);
                ~AVLTree();
                Node* search(Key key);
                bool insert(value_type data);
                bool remove(Key key);
                void show();
                int height();
                int size();
                bool check();
                // Post-fix ++
                AVLTree operator++(int) {
                    AVLTree iterator = *this;
                    cout << "Position before: " << get<0>(position->data) << endl;
                    // data++;
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
                    cout << "Position after: " << get<0>(position->data) << endl;
                    
                    return iterator;
                }

                reference operator*() {
                    return position;
                }

                bool operator==(const AVLTree& rightSide) {
                    return position == rightSide.position;
                }

                void set(Node* value) {
                    this->position = value;
                }

                Node* getRoot() {
                    return root;
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
                void copyTree(AVLNode* &thisRoot, AVLNode* &sourceRoot);
                void insertionRebalance(AVLNode* &node);
                void deletionRebalance(AVLNode* &node);
                bool insertHelper(AVLNode* &node, value_type data, bool& flag);
                int calculateHeight(AVLNode* node);
                void showInorder(AVLNode* node);
                void showPostorder(AVLNode* node);
                void rrRotation(AVLNode* &node, bool isInsert);
                void rlRotation(AVLNode* &node, bool isInsert);
                void llRotation(AVLNode* &node, bool isInsert);
                void lrRotation(AVLNode* &node, bool isInsert);
                value_type deleteMax(AVLNode* &node);
                void rotate(AVLNode* &node);
                Node* searchHelper(AVLNode* node, Key key);
                void removeBoth(AVLNode* node);
                void removeNode(AVLNode* &node, bool& flag);
                bool removeHelper(AVLNode* &node, Key key, bool& flag);
                void calculateBalanceFactors(AVLNode* &node);
                int sizeHelper(AVLNode* node, int &size);
                bool checkHelper(AVLNode* node);
        };

        explicit MyMap(const Compare& comp = Compare(), const Allocator& = Allocator());
        MyMap(const MyMap<Key, T, Compare, Allocator>& x);
        ~MyMap();
        AVLTree begin();
        AVLTree end();
        bool empty () const;
        size_type size() const;
        T& operator[](const key_type& x);
        pair<AVLTree, bool> insert(const value_type& x);   // Should be pair<iterator, bool> insert(const value_type& x); but compiler doesn't like pair here for some reason...
        size_type erase(const key_type& x);
        void clear();
        AVLTree find(const key_type& x);

    private:
        // value_type pair;
        AVLTree* iter;
};