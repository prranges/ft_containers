#pragma once

#include "Pair.hpp"
#include "BD_Iterator.hpp"

namespace ft {
    enum node_color { Black, Red };

    template<class value_type>
    struct node {
        value_type* key_value; // pair
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
        ~node() {}
    };

    template<class value_type>
    class RB_Tree {
    private:
        node<value_type> nil;
        node<value_type>* root;
        size_t _size;
    public:
        typedef typename value_type::first_type	    key_type;
        typedef typename value_type::second_type    mapped_type;

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

        void clear_node(node<value_type> *n) {
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

        void insert_node(const value_type &key_value, node<value_type>* x) {
            if (x == 0)
                x = root;
            node<value_type>* n = new node<value_type>(key_value);
            node<value_type>* y = &nil;

            while (!x->NIL)
            {
                y = x;
                if (n->key_value->first < x->key_value->first)
                    x = x->left;
                else
                    x = x->right;
            }
            n->parent = y;
            if (y->NIL)
                root = n;
            else if (n->key_value->first < y->key_value->first)
                y->left = n;
            else
                y->right = n;
            n->left = &nil;
            n->right = &nil;
            n->color = Red;
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

        int delete_node(node<value_type>* n) {
            node<value_type>* x;
            node<value_type>* y;

            if (!n || n->NIL)
                return 0;
            if (n->left->NIL || n->right->NIL) {
                y = n;
            } else {
                y = n->right;
                while (!y->left->NIL)
                    y = y->left;
            }
            if (!y->left->NIL) {
                x = y->left;
            } else
                x = y->right;
            x->parent = y->parent;
            if (y->parent) {
                if (y == y->parent->left)
                    y->parent->left = x;
                else
                    y->parent->right = x;
            } else
                root = x;
            if (y != n) {
                delete n->key_value;
                value_type *p = new value_type(*y->key_value);
                n->key_value = p;
            }
            if (y->color == 0) {
                delete_fixup (x);
            }
            nil.parent = last(); /// added
            nil.begin = begin(); /// added
            --_size;
            delete y;
            return 1;
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

        node<value_type>* search(key_type key) {
            node<value_type>* n = &nil;
            node<value_type>* node = root;

            while (!node->NIL) {
                n = node;
                if (node->key_value->first == key)
                    return node;
                if (key < node->key_value->first)
                    node = node->left;
                else
                    node = node->right;
            }
            return node;
        }

        size_t size() const {
            return _size;
        }






        void printBT(const std::string& prefix, const node<value_type>* nodeV, bool isLeft) const {
            std::cout << prefix;
            std::cout << (isLeft ? "├──" : "└──" );

            if (nodeV->NIL){
                std::cout <<"\033[0;36m"<< "nil" << "\033[0m"<<std::endl;
                return ;
            }

            // print the value of the node
            if (nodeV->color == 0)
                std::cout <<"\033[0;36m"<< nodeV->key_value->first <<"\033[0m"<<std::endl;
            else
                std::cout <<"\033[0;31m"<< nodeV->key_value->first << "\033[0m"<<std::endl;
            printBT( prefix + (isLeft ? "│   " : "    "), nodeV->left, true);
            printBT( prefix + (isLeft ? "│   " : "    "), nodeV->right, false);
        }

        void printTree(){
            printBT("" , root, false);
        }
    };
}