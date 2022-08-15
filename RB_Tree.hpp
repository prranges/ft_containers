#pragma once

namespace ft {
    enum RBTColor { Black, Red };

    template<class value_type>
    struct Node {
        RBTColor color;
        Node *begin;
        Node *left;
        Node *right;
        Node *parent;
        bool NIL;
        value_type *pair;

        Node() : pair(new value_type()), color(Black), begin(NULL), left(this), right(this), parent(0), NIL(1) {}
        explicit Node(const value_type& p) : pair(new value_type(p)), color(Black), begin(NULL), left(this), right(this), parent(0), NIL(0) {}
        ~Node() {}
    };

    template <class Key, class Value>
    struct pair {
        typedef Key		first_type;
        typedef Value	second_type;
        first_type		first;
        second_type		second;

        pair() : first(first_type()), second(second_type()) {}
        pair(const first_type& a, const second_type& b) : first(a), second(b) {}

        template<class K, class V>
        pair(const pair<K, V> &other) : first(static_cast<Key>(other.first)), second(static_cast<Value>(other.second)) {}

        pair &operator= (const pair &other) {
            first = other.first;
            second = other.second;
            return *this;
        }
    };

    template <class T1, class T2>
    bool operator==(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class T1, class T2>
    bool operator!=(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<=(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>=(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return !(lhs < rhs);
    }

    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {
        return ft::pair<T1, T2>(x, y);
    }

    template<class value_type>
    class RB_Tree {
    public:
        Node<value_type> nil;
        Node<value_type>* root;
        size_t tree_size;

        RB_Tree() : tree_size(0) {
            root = &nil;
            nil.color = Black;
            nil.NIL = true;
            nil.parent = 0;
            nil.left = &nil;
            nil.right = &nil;
            nil.begin = &nil;
        }

        RB_Tree(RB_Tree<value_type>& other) : tree_size(0) {
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
                tree_size = other.tree_size;
            }
            return *this;
        }

        void rotateLeft(Node<value_type>* x) {
            Node<value_type> *y = x->right;

            x->right = y->left;
            if (!y->left->NIL)  y->left->parent = x;
            if (!y->NIL) y->parent = x->parent;
            if (x->parent) {
                if (x == x->parent->left) {
                    x->parent->left = y;
                }
                else {
                    x->parent->right = y;
                }
            } else {
                root = y;
            }
            y->left = x;
            if (!x->NIL) x->parent = y;
        }

        void rotateRight(Node<value_type> *x) {
            Node<value_type> *y = x->left;

            x->left = y->right;
            if (!y->right->NIL) y->right->parent = x;
            if (!y->NIL) y->parent = x->parent;
            if (x->parent) {
                if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
            } else {
                root = y;
            }
            y->right = x;
            if (!x->NIL) x->parent = y;
        }

        void insertFixup(Node<value_type>* x) {
            while (x != root && x->parent->color == Red) {
                if (x->parent == x->parent->parent->left) {
                    Node<value_type> *y = x->parent->parent->right;
                    if (y->color == Red) {
                        x->parent->color = Black;
                        y->color = Black;
                        x->parent->parent->color = Red;
                        x = x->parent->parent;
                    } else {
                        if (x == x->parent->right) {
                            x = x->parent;
                            rotateLeft(x);
                        }
                        x->parent->color = Black;
                        x->parent->parent->color = Red;
                        rotateRight(x->parent->parent);
                    }
                } else {
                    Node<value_type> *y = x->parent->parent->left;
                    if (y->color == Red) {
                        x->parent->color = Black;
                        y->color = Black;
                        x->parent->parent->color = Red;
                        x = x->parent->parent;
                    } else {
                        if (x == x->parent->left) {
                            x = x->parent;
                            rotateRight(x);
                        }
                        x->parent->color = Black;
                        x->parent->parent->color = Red;
                        rotateLeft(x->parent->parent);
                    }
                }
            }
            root->color = Black;
        }

        void deleteFixup(Node<value_type>* x) {
            while (x != root && x->color == Black) {
                if (x == x->parent->left) {
                    Node<value_type> *w = x->parent->right;
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
                    Node<value_type> *w = x->parent->left;
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

        int deleteNode(Node<value_type>* z) {
            Node<value_type> *x, *y;

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
                value_type *p = new value_type(*y->pair);
                z->pair = p;
            }
            if (y->color == Black)
                deleteFixup (x);
            nil.parent = last();
            nil.begin = begin();
            --tree_size;
            delete y;
            return 1;
        }

        Node<value_type>* begin() {
            Node<value_type>* tmp = root;
            while (!tmp->left->NIL) {
                tmp = tmp->left;
            }
            return tmp;
        }

        Node<value_type>* last() {
            Node<value_type>* tmp = root;
            while (!tmp->right->NIL) {
                tmp = tmp->right;
            }
            return tmp;
        }

        Node<value_type>* end() {
            Node<value_type>* tmp = root;
            while (!tmp->right->NIL) {
                tmp = tmp->right;
            }
            return tmp->right;
        }
    };
}