#pragma once

#include "Pair.hpp"
#include "BD_Iterator.hpp"
#include <iostream>


namespace ft {
    enum node_color { Black, Red };

    template<class value_type>
    struct node {
        value_type* key_value;
        node_color  color;
        node*       left;
        node*       right;
        node*       parent;
        bool        NIL;
        node*       begin;

        /// Constructors
        node() : key_value(new value_type()), color(Black), left(this), right(this), parent(0), NIL(1), begin(NULL) {}
        node(const value_type& n) : key_value(new value_type(n)), color(Black), left(this), right(this), parent(0), NIL(0), begin(NULL) {}

        /// Destructor
        ~node() { delete key_value; }
    };

    template<class value_type>
    class RB_Tree {
    public:
        node<value_type> nil;
        node<value_type>* root;
        size_t _size;

        /// Constructors
        RB_Tree() : _size(0) {
            root = &nil;
            nil.color = Black;
            nil.NIL = true;
            nil.parent = 0;
            nil.left = &nil;
            nil.right = &nil;
            nil.begin = &nil;
        }

        RB_Tree(RB_Tree<value_type>& other) : _size(0) {
            root = &nil;
            nil.color = Black;
            nil.NIL = (&other == &other);
            nil.parent = 0;
            nil.left = &nil;
            nil.right = &nil;
            nil.begin = &nil;
        }

        RB_Tree& operator= (const RB_Tree<value_type>& other) {
            if (this != &other) {
                root = other.root;
                nil = other.nil;
                _size = other._size;
            }
            return *this;
        }

        void clear_node (node<value_type> *n) {
            if (!n->NIL){
                clear_node(n->right);
                clear_node(n->left);
                delete n;
            }
        }

        void clear () {
            clear_node(root);
            root = &nil;
            nil.parent = NULL;
            _size = 0;
        }


        void left_rotate(node<value_type>* x) {
            node<value_type>* y = x->right;
            x->right = y->left;

            if (!y->left->NIL)
                y->left->parent = x;
            y->parent = x->parent;
            if (x->parent->NIL)
                root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }

        void right_rotate(node<value_type>* x) {
            node<value_type>* y = x->left;
            x->left = y->right;

            if (!y->right->NIL)
                y->right->parent = x;
            y->parent = x->parent;
            if (x->parent->NIL)
                root = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y;
        }

        template<class Compare>
        void insert_node(const value_type &value, node<value_type>* x, Compare& _comp) {
            if (x == 0)
                x = root;
            node<value_type>* n = new node<value_type>(value);
            node<value_type>* y = &nil;

            while (!x->NIL) {
                y = x;
                x = _comp(value.first, x->key_value->first) ? x->left : x->right;
            }
            n->parent = y;
            n->left = &nil;
            n->right = &nil;
            n->color = Red;
            if (y->NIL)
                root = n;
            else if (_comp(n->key_value->first, y->key_value->first))
                y->left = n;
            else
                y->right = n;
            if (n == last()) { nil.parent = n; }
            if (n == begin()) { nil.begin = n; }
            ++_size;
            insert_fixup(n);
        }

        template<class Compare>
        void insert_node_set(const value_type &value, node<value_type>* x, Compare& _comp) {
            if (x == 0)
                x = root;
            node<value_type>* n = new node<value_type>(value);
            node<value_type>* y = &nil;

            while (!x->NIL) {
                y = x;
                x = _comp(value, *x->key_value) ? x->left : x->right;
            }
            n->parent = y;
            n->left = &nil;
            n->right = &nil;
            n->color = Red;
            if (y->NIL)
                root = n;
            else if (_comp(*n->key_value, *y->key_value))
                y->left = n;
            else
                y->right = n;
            if (n == last()) { nil.parent = n; }
            if (n == begin()) { nil.begin = n; }
            ++_size;
            insert_fixup(n);
        }

        void insert_fixup(node<value_type>* x) {
            while (x != root && x->parent->color == Red) {
                if (x->parent == x->parent->parent->left) {
                    node<value_type>* y = x->parent->parent->right;
                    if (y->color == Red) {
                        x->parent->color = Black;
                        y->color = Black;
                        x->parent->parent->color = Red;
                        x = x->parent->parent;
                    } else {
                        if (x == x->parent->right) {
                            x = x->parent;
                            left_rotate(x);
                        }
                        x->parent->color = Black;
                        x->parent->parent->color = Red;
                        right_rotate(x->parent->parent);
                    }
                } else {
                    node<value_type>* y = x->parent->parent->left;
                    if (y->color == Red) {
                        x->parent->color = Black;
                        y->color = Black;
                        x->parent->parent->color = Red;
                        x = x->parent->parent;
                    } else {
                        if (x == x->parent->left) {
                            x = x->parent;
                            right_rotate(x);
                        }
                        x->parent->color = Black;
                        x->parent->parent->color = Red;
                        left_rotate(x->parent->parent);
                    }
                }
            }
            root->color = Black;
        }

        void swich_node(node <value_type> *u, node <value_type> *v) {
            if (u->parent->NIL)
                root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            v->parent = u->parent;
        }

        void delete_node(node <value_type> *z) {
            node <value_type> *y = z;
            node <value_type> *x;
            node_color y_color = y->color;
            if (z->left->NIL) {
                x = z->right;
                swich_node(z, z->right);
            } else if (z->right->NIL) {
                x = z->left;
                swich_node(z, z->left);
            } else {
                y = z->right;
                while (!y->left->NIL)
                    y = y->left;
                y_color = y->color;
                x = y->right;
                if (y->parent == z)
                    x->parent = y;
                else{
                    swich_node(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                swich_node(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            _size--;
            if (y_color == Black)
                delete_fixup(x);
            nil.parent = last();
            nil.begin = begin();
            delete z;
        }

        void delete_fixup(node<value_type>* x) {
            while (x != root && x->color == Black) {
                if (x == x->parent->left) {
                    node<value_type> *w = x->parent->right;
                    if (w->color == Red) {
                        w->color = Black;
                        x->parent->color = Red;
                        left_rotate(x->parent);
                        w = x->parent->right;
                    }
                    if (w->left->color == Black && w->right->color == Black) {
                        w->color = Red;
                        x = x->parent;
                    } else {
                        if (w->right->color == Black) {
                            w->left->color = Black;
                            w->color = Red;
                            right_rotate(w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = Black;
                        w->right->color = Black;
                        left_rotate (x->parent);
                        x = root;
                    }
                } else {
                    node<value_type> *w = x->parent->left;
                    if (w->color == Red) {
                        w->color = Black;
                        x->parent->color = Red;
                        right_rotate(x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == Black && w->left->color == Black) {
                        w->color = Red;
                        x = x->parent;
                    } else {
                        if (w->left->color == Black) {
                            w->right->color = Black;
                            w->color = Red;
                            left_rotate (w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = Black;
                        w->left->color = Black;
                        right_rotate (x->parent);
                        x = root;
                    }
                }
            }
            x->color = Black;
        }

        node<value_type>* begin() {
            node<value_type>* tmp = root;

            while (!tmp->left->NIL) {
                tmp = tmp->left;
            }
            return tmp;
        }

        node<value_type>* begin() const {
            node<value_type>* tmp = root;

            while (!tmp->left->NIL) {
                tmp = tmp->left;
            }
            return tmp;
        }

        node<value_type>* last() {
            node<value_type>* tmp = root;

            while (!tmp->right->NIL) {
                tmp = tmp->right;
            }
            return tmp;
        }

        node<value_type>* last() const {
            node<value_type>* tmp = root;

            while (!tmp->right->NIL) {
                tmp = tmp->right;
            }
            return tmp;
        }

        node<value_type>* end() {
            node<value_type>* tmp = root;

            while (!tmp->right->NIL) {
                tmp = tmp->right;
            }
            return tmp->right;
        }

        node<value_type>* end() const {
            node<value_type>* tmp = root;

            while (!tmp->right->NIL) {
                tmp = tmp->right;
            }
            return tmp->right;
        }

        size_t size() const {
            return _size;
        }
    };
}