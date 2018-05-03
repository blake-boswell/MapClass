// #include "MyMap.h"
#include "AVLtree.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main() {
    // MyMap<int, int> map;
    AVLTree<int, int>* avl = new AVLTree<int, int>();
    pair<int, int> record = make_pair(1,4);

    // Remove tests
        AVLTree<int,int>* llAVL = new AVLTree<int,int>();
        record = make_pair(10, 50);
        llAVL->insert(record);  // Key 10
        record = make_pair(5, 25);
        llAVL->insert(record);  // Key 5
        record = make_pair(18, 90);
        llAVL->insert(record);  // Key 18
        record = make_pair(2, 10);
        llAVL->insert(record);  // Key 2
        record = make_pair(7, 35);
        llAVL->insert(record);  // Key 7
        record = make_pair(16, 80);
        llAVL->insert(record);  // Key 16
        record = make_pair(20, 100);
        llAVL->insert(record);  // Key 20
        record = make_pair(1, 5); 
        llAVL->insert(record);  // Key 1
        record = make_pair(12, 60);
        llAVL->insert(record);  // Key 12
        record = make_pair(19, 95);
        llAVL->insert(record);  // Key 19
        record = make_pair(22, 110);
        llAVL->insert(record);  // Key 22
        record = make_pair(23, 115);
        llAVL->insert(record);  // Key 23
        llAVL->show();
        cout << "\n\nTesting remove rotations\n\n" << endl;
        cout << "Removing 7 for LL ROT on 5" << endl;
        llAVL->remove(7);
        llAVL->show();
        cout << "Is AVL: " << llAVL->check() << endl;
        cout << "\n\n\n";
        
        // AVLTree<int,int>* lrAVL = new AVLTree<int,int>();
        // lrAVL->insert(10);
        // lrAVL->insert(5);
        // lrAVL->insert(18);
        // lrAVL->insert(2);
        // lrAVL->insert(7);
        // lrAVL->insert(16);
        // lrAVL->insert(20);
        // lrAVL->insert(3);
        // lrAVL->insert(12);
        // lrAVL->insert(19);
        // lrAVL->insert(22);
        // lrAVL->insert(23);
        // lrAVL->show();
        // cout << "Testing remove rotations" << endl;
        // cout << "Removing 7 for LR ROT on 5" << endl;
        // lrAVL->remove(7);
        // lrAVL->show();
        // cout << "Is AVL: " << lrAVL->check() << endl;
        // cout << "\n\n\n";

        // AVLTree<int,int>* rrAVL = new AVLTree<int,int>();
        // rrAVL->insert(10);
        // rrAVL->insert(5);
        // rrAVL->insert(18);
        // rrAVL->insert(2);
        // rrAVL->insert(7);
        // rrAVL->insert(16);
        // rrAVL->insert(20);
        // rrAVL->insert(1);
        // rrAVL->insert(12);
        // rrAVL->insert(19);
        // rrAVL->insert(22);
        // rrAVL->insert(23);
        // rrAVL->show();
        // cout << "Testing remove rotations" << endl;
        // cout << "Removing 19 for RR ROT on 20" << endl;
        // rrAVL->remove(19);
        // rrAVL->show();
        // cout << "Is AVL: " << rrAVL->check() << endl;
        // cout << "\n\n\n";

        // AVLTree<int,int>* rlAVL = new AVLTree<int,int>();
        // rlAVL->insert(10);
        // rlAVL->insert(5);
        // rlAVL->insert(18);
        // rlAVL->insert(2);
        // rlAVL->insert(7);
        // rlAVL->insert(16);
        // rlAVL->insert(20);
        // rlAVL->insert(1);
        // rlAVL->insert(12);
        // rlAVL->insert(19);
        // rlAVL->insert(22);
        // rlAVL->insert(21);
        // rlAVL->show();
        // cout << "Testing remove rotations" << endl;
        // cout << "Removing 19 for RL ROT on 20" << endl;
        // rlAVL->remove(19);
        // rlAVL->show();
        // cout << "Is AVL: " << rlAVL->check() << endl;

    return 0;
}