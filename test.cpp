// #include "MyMap.h"
#include "MyMap.cpp"
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main() {
    // MyMap<int, int> map;
    // AVLTree<int, int>* avl = new AVLTree<int, int>();
    pair<int, int> record = make_pair(1,4);

    // Remove tests
    MyMap<int, int> map;
    MyMap<int, int>::AVLTree i;

    // cout << "Is Empty: " << map.empty() << endl;
    record = make_pair(10, 50);
    map.insert(make_pair(10, 50));  // Key 10
    cout << "Insertion over." << endl;
    cout << map[10] << endl;

    // record = make_pair(5, 25);
    // map.insert(make_pair(5, 25));  // Key 5
    // record = make_pair(18, 90);
    // map.insert(make_pair(18, 90));  // Key 18
    // record = make_pair(2, 10);
    // map.insert(make_pair(2, 10));  // Key 2
    // record = make_pair(7, 35);
    // map.insert(make_pair(7, 35));  // Key 7
    // record = make_pair(16, 80);
    // map.insert(make_pair(16, 80));  // Key 16
    // record = make_pair(20, 100);
    // map.insert(make_pair(20, 100));  // Key 20
    // record = make_pair(1, 5); 
    // map.insert(make_pair(1, 5));  // Key 1
    // record = make_pair(12, 60);
    // map.insert(make_pair(12, 60));  // Key 12
    // record = make_pair(19, 95);
    // map.insert(make_pair(19, 95));  // Key 19
    // record = make_pair(22, 110);
    // map.insert(make_pair(22, 110));  // Key 22
    // record = make_pair(23, 115);
    // map.insert(make_pair(23, 115));  // Key 23

    //cout << "Size of map: " << map.size() << endl;

    // for(i = map.begin(); i != map.end(); i++) {
    //     cout << i->first << endl;
    // }


    // map.show();
    // cout << "\n\nTesting remove rotations\n\n" << endl;
    // cout << "Removing 7 for LL ROT on 5" << endl;
    // map.remove(7);
    // map.show();
    // cout << "Is AVL: " << map.check() << endl;
    // cout << "\n\n\n";

    //MyMap<int, int>::AVLTree i = map.begin();
    // i++;
    // i++;
        
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