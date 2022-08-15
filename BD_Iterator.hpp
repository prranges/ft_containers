#pragma once

#include "Iterator_traits.hpp"

namespace ft {
    template <class T>
    class BD_Iterator {
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
            if (_node->NIL && _node->begin != _node) _node = _node->begin;
            else if (!_node->right->NIL) {
                _node = min_node(_node->right);
            } else {
                T current = _node;
                T tmp = _node;
                _node = _node->parent;
                if (!_node) { _node = current->right; return; }
                while (_node->left != tmp) {
                    if (!_node->parent) { _node = current->right; break; }
                    tmp = _node;
                    _node = _node->parent;
                }
            }
        }

        void prev() {
            if (_node->NIL) _node = _node->parent;
            else if (!_node->left->NIL) {
                _node = max_node(_node->left);
            } else {
                T tmp = _node;
                _node = _node->parent;
                while (_node->right != tmp) {
                    tmp = _node;
                    if (!_node->parent) { _node = tmp->left - 1; break; }
                    _node = _node->parent;
                }
            }
        }
    public:
        typedef T                                               iterator_type;
        typedef typename iterator_traits<T>::difference_type    difference_type;
        typedef typename iterator_traits<T>::value_type         value_type;
        typedef typename iterator_traits<T>::pointer            pointer;
        typedef typename iterator_traits<T>::const_pointer		const_pointer;
        typedef typename iterator_traits<T>::reference          reference;
        typedef typename iterator_traits<T>::const_reference	const_reference;
        typedef typename iterator_traits<T>::iterator_category  iterator_category;

        /// CONSTRUCTORS
        BD_Iterator() : _node() {}
        explicit BD_Iterator(T node) : _node(node) {}
        BD_Iterator(const BD_Iterator& other) : _node(other._node) {}

        /// DESTRUCTOR
        ~BD_Iterator() {}

        /// OPERATORS
        template <class Type>
        operator BD_Iterator<Type>() const {
            return RA_Iterator<Type>(_node);
        }

        template <class Iterator>
        BD_Iterator& operator= (BD_Iterator<Iterator> const & other) {
            _node = & (*other._node);
            return *this;
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

        reference operator* () const {
            return *_node->pair;
        }

        pointer operator-> () const {
            return _node->pair;
        }

        iterator_type base() const { return _node; }
    };

    template <class Iterator1, class Iterator2>
    bool operator== (const BD_Iterator<Iterator1>& a, const BD_Iterator<Iterator2>& b) {
        return a.base() == b.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator!= (const BD_Iterator<Iterator1>& a, const BD_Iterator<Iterator2>& b) {
        return !(a.base() == b.base());
    }
}