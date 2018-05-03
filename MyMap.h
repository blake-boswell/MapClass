#include <iostream>
#include <utility>
#include "AVLTree.h"
using std::pair;
using std::less;
using std::cout;
using std::allocator;

template <class Key, class T, class Compare = less<Key>, class Allocator = allocator<pair<const Key, T>>>
class MyMap {
    typedef pair<const Key, T> value_type;
    typedef unsigned size_type;
    typedef Key key_type;
    private:
        // value_type pair;
        iterator<Key, T> iter;
    public:
        class iterator: public AVLTree<Key, T> {
            private:
            public:
                iterator();
                ~iterator();
                iterator operator*() {

                }
                // Post-fix ++
                iterator operator++(int) {
                    // data++;
                }
                void set(int value) {
                    // data = value;
                }
                void test(value_type testVal) {
                    insert(testVal);
                }
        };
        explicit MyMap(const Compare& comp = Compare(), const Allocator& = Allocator());
        MyMap(const MyMap<Key, T, Compare, Allocator>& x);
        ~MyMap();
        iterator begin();
        iterator end();
        bool empty () const;
        size_type size() const;
        T& operator[](const key_type& x);
        bool insert(const value_type& x);   // Should be pair<iterator, bool> insert(const value_type& x); but compiler doesn't like pair here for some reason...
        size_type erase(const key_type& x);
        void clear();
        iterator find(const key_type& x);
};