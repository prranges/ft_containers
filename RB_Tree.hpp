#pragma once

#include "Pair.hpp"

namespace ft {
    enum node_color { Black, Red };

    template<class value_type>
    struct node {
        value_type  key_value;
        node_color  color;

//        node*       begin;
        node*       left;
        node*       right;
        node*       parent;
        bool        NIL;

        /// Constructors
        node() : key_value(value_type()), color(Black), left(this), right(this), parent(0), NIL(1) {}
        explicit node(const value_type& n) : key_value(value_type(n)), color(Black), left(this), right(this), parent(0), NIL(0) {}

        /// Destructor
        ~node() {}
    };

    template<class value_type>
    class RB_Tree {
    private:
        node<value_type> nil;
        node<value_type>* root;
        size_t tree_size;
    public:
        typedef typename value_type::first_type	    key_type;
        typedef typename value_type::second_type    mapped_type;

        /// Constructors
        RB_Tree() : tree_size(0) {
            root = &nil;
            nil.color = Black;
            nil.NIL = true;
            nil.parent = 0;
            nil.left = &nil;
            nil.right = &nil;
//            nil.begin = &nil;
        }

        RB_Tree(RB_Tree<value_type>& other) : tree_size(0) {
            root = &nil;
            nil.color = Black;
            nil.NIL = (&other == &other);
            nil.parent = 0;
            nil.left = &nil;
            nil.right = &nil;
//            nil.begin = &nil;
        }

        RB_Tree& operator= (const RB_Tree<value_type>& other) {
            if (this != &other) {
                root = other.root;
                nil = other.nil;
                tree_size = other.tree_size;
            }
            return *this;
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

        void insert_node(const value_type &kv, node<value_type>* x) {
            if (x == 0)
                x = root;
            node<value_type>* z = new node<value_type>(kv);
            node<value_type>* y = &nil;

            while (!x->NIL)
            {
                y = x;
                if (z->key_value.first < x->key_value.first)
                    x = x->left;
                else
                    x = x->right;
            }
            z->parent = y;
            if (y->NIL)
                root = z;
            else if (z->key_value.first < y->key_value.first)
                y->left = z;
            else
                y->right = z;
            z->left = &nil;
            z->right = &nil;
            z->color = Red;
            tree_size++;
            insert_fixup(z);
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

        void delete_fixup(node<value_type>* x) {
            while (x != root && x->color == Black) {
                if (x == x->parent->left) {
                    node<value_type> *w = x->parent->right;
                    if (w->color == Red) {
                        w->color = Black;
                        x->parent->color = Red;
                        rotateLeft (x->parent);
                        w = x->parent->right;
                    }
                    if (w->left->color == Black && w->right->color == Black) {
                        w->color = Red;
                        x = x->parent;
                    } else {
                        if (w->right->color == Black) {
                            w->left->color = Black;
                            w->color = Red;
                            rotateRight (w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = Black;
                        w->right->color = Black;
                        rotateLeft (x->parent);
                        x = root;
                    }
                } else {
                    node<value_type> *w = x->parent->left;
                    if (w->color == Red) {
                        w->color = Black;
                        x->parent->color = Red;
                        rotateRight (x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == Black && w->left->color == Black) {
                        w->color = Red;
                        x = x->parent;
                    } else {
                        if (w->left->color == Black) {
                            w->right->color = Black;
                            w->color = Red;
                            rotateLeft (w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = Black;
                        w->left->color = Black;
                        rotateRight (x->parent);
                        x = root;
                    }
                }
            }
            x->color = Black;
        }

        int delete_node(node<value_type>* z) {
            node<value_type>* x;
            node<value_type>* y;

            if (!z || z->NIL)
                return 0;
            if (z->left->NIL || z->right->NIL) {
                y = z;
            } else {
                y = z->right;
                while (!y->left->NIL)
                    y = y->left;
            }
            if (!y->left->NIL)
                x = y->left;
            else
                x = y->right;
            x->parent = y->parent;
            if (y->parent)
                if (y == y->parent->left)
                    y->parent->left = x;
                else
                    y->parent->right = x;
            else
                root = x;
            if (y != z) {
                delete z->pair;
                value_type* p = new value_type(*y->pair);
                z->pair = p;
            }
            if (y->color == Black)
                delete_fixup (x);
            nil.parent = last();
            nil.begin = begin();
            --tree_size;
            delete y;
            return 1;
        }

        node<value_type>* begin() {
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

        node<value_type>* end() {
            return last()->right;
        }




        void printBT(const std::string& prefix, const node<value_type>* nodeV, bool isLeft) const
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );


            if (nodeV->NIL){
                std::cout <<"\033[0;36m"<< "nil" << "\033[0m"<<std::endl;
                return ;
            }

            // print the value of the node
            if (nodeV->color == 0)
                std::cout <<"\033[0;36m"<< nodeV->key_value.first <<"\033[0m"<<std::endl;
            else
                std::cout <<"\033[0;31m"<< nodeV->key_value.first << "\033[0m"<<std::endl;
            printBT( prefix + (isLeft ? "│   " : "    "), nodeV->left, true);
            printBT( prefix + (isLeft ? "│   " : "    "), nodeV->right, false);
        }

        void printTree(){
            printBT("" , root, false);
        }



    };
}