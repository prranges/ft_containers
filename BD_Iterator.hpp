#pragma once

#include "Iterator_traits.hpp"
#include "Utility.hpp"

namespace ft {
    template<class T, class Pair> class BD_Iterator {
    private:
        T _node;

        T min_node(T node) const {
            if (node->left->NIL)
                return node;
            return min_node(node->left);
        }

        T max_node(T node) const {
            if (node->right->NIL)
                return node;
            return max_node(node->right);
        }

        void next() {
            if (_node->NIL)
                _node = _node->parent;
            else if (!_node->right->NIL)
                _node = min_node(_node->right);
            else {
                T parent = _node->parent;
                while (!parent->NIL && _node == parent->right) {
                    _node = parent;
                    parent = parent->parent;
                }
                _node = parent;
            }
        }

        void prev()
        {
            if (_node->NIL)
                _node = _node->parent;
            else if (!_node->left->NIL)
                _node = max_node(_node->left);
            else {
                T parent = _node->parent;
                while (!parent->NIL && _node == parent->left) {
                    _node = parent;
                    parent = parent->parent;
                }
                _node = parent;
            }
        }

    public:
        typedef typename iterator_traits<T*>::difference_type   difference_type;
        typedef typename iterator_traits<T*>::value_type        value_type;
        typedef Pair*                                           pointer;
        typedef const Pair*                                     const_pointer;
        typedef Pair&                                           reference;
        typedef const Pair&                                     const_reference;
        typedef typename iterator_traits<T>::iterator_category  iterator_category;

        /// CONSTRUCTORS
        BD_Iterator(T value = 0): _node(value) {}

        template<class U>
        BD_Iterator(const BD_Iterator<U, Pair>& other) : _node(other.base()) {}

        /// DESTRUCTOR
        ~BD_Iterator() {}

        /// OPERATORS
        BD_Iterator& operator= (BD_Iterator const & other) {
            _node = other.base();
            return *this;
        }

        reference operator* () const {
            return *_node->key_value;
        }

        pointer operator-> () const {
            return _node->key_value;
        }

        BD_Iterator& operator++ () {
            next();
            return *this;
        }

        BD_Iterator operator++ (int) {
            BD_Iterator tmp(*this);
            next();
            return tmp;
        }

        BD_Iterator& operator-- () {
            prev();
            return *this;
        }

        BD_Iterator operator-- (int) {
            BD_Iterator tmp(*this);
            prev();
            return tmp;
        }

        T base() const {
            return _node;
        }

        bool operator== (BD_Iterator const & other) const {
            return _node == other._node;
        };

        bool operator!= (BD_Iterator const & other) const {
            return _node != other._node;
        };

    };
}
