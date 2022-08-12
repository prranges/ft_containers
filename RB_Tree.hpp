#pragma once

namespace ft {
    enum RBTColor { Black, Red };

    template<class Т>
    struct Node {
        RBTColor color;
        struct Node *begin;
        struct Node *left;
        struct Node *right;
        struct Node *parent;
        bool NIL;
        Т *pair;

        Node() : pair(new Т()), color(Black), begin(NULL), left(this), right(this), parent(0), NIL(1) {}
        explicit Node(const Т& p) : pair(new Т(p)), color(Black), begin(NULL), left(this), right(this), parent(0), NIL(0) {}
        ~Node() { delete pair; }
    };

    template<class T>
    class RB_Tree {
    private:
        Node<T> nil;
        Node<T>* root;
        size_t tree_size;
    public:
        typedef typename T::first_type  key_type;
        typedef typename T::second_type mapped_type;

        RB_Tree() : tree_size(0) {
            root = &nil;
            nil.color = Black;
            nil.NIL = true;
            nil.parent = 0;
            nil.left = &nil;
            nil.right = &nil;
            nil.begin = &nil;
        }

        RB_Tree(RB_Tree<T>& other) : tree_size(0) {
            root = &nil;
            nil.color = Black;
            nil.NIL = (&other == &other);
            nil.parent = 0;
            nil.left = &nil;
            nil.right = &nil;
            nil.begin = &nil;
        }

        RB_Tree& operator= (const RB_Tree<T>& other) {
            if (this != &other) {
                root = other.root;
                nil = other.nil;
                tree_size = other.tree_size;
            }
            return *this;
        }

        void rotateLeft(Node<T> *x) {
            Node<T> *y = x->right;

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

        void rotateRight(Node<T> *x) {
            Node<T> *y = x->left;

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

        void insertFixup(Node<T> *x) {
            while (x != root && x->parent->color == Red) {
                if (x->parent == x->parent->parent->left) {
                    Node<T> *y = x->parent->parent->right;
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
                    Node<T> *y = x->parent->parent->left;
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

        void deleteFixup(Node<T> *x) {
            while (x != root && x->color == Black) {
                if (x == x->parent->left) {
                    Node<T> *w = x->parent->right;
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
                    Node<T> *w = x->parent->left;
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

        int deleteNode(Node<T> *z) {
            Node<T> *x, *y;

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
                T *p = new T(*y->pair);
                z->pair = p;
            }
            if (y->color == Black)
                deleteFixup (x);
            nil.parent = getLast();
            nil.begin = getBegin();
            tree_size--;
            delete y;
            return 1;
        }

        Node<T>* getBegin() {
            Node<T>* tmp = root;
            while (!tmp->left->NIL) {
                tmp = tmp->left;
            }
            return tmp;
        }

        Node<T>* getLast() {
            Node<T>* tmp = root;
            while (!tmp->right->NIL) {
                tmp = tmp->right;
            }
            return tmp;
        }

        Node<T>* getEnd() {
            Node<T>* tmp = root;
            while (!tmp->right->NIL) {
                tmp = tmp->right;
            }
            return tmp->right;
        }
    };
}