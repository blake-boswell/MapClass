#include "MyMap.h"

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::MyMap(const Compare& comp, const Allocator& alloc) {
    cout << "Default constructor" << endl;
}

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::MyMap(const MyMap<Key, T, Compare, Allocator>& x) {
    cout << "Copy constructor" << endl;
}

template <class Key, class T, class Compare, class Allocator>
MyMap<Key, T, Compare, Allocator>::~MyMap() {
     cout << "Destructor" << endl;
}