#pragma once
#include "Iterator_traits.hpp"

namespace ft {
    template <class T> class RE_Iterator {
        private:
            T _base_iterator;
        public:
            typedef T                                               iterator_type;
            typedef typename iterator_traits<T>::value_type         value_type;
            typedef typename iterator_traits<T>::difference_type    difference_type;
            typedef typename iterator_traits<T>::pointer            pointer;
            typedef typename iterator_traits<T>::const_pointer      const_pointer;
            typedef typename iterator_traits<T>::reference          reference;
            typedef typename iterator_traits<T>::const_reference    const_reference;
            typedef typename iterator_traits<T>::iterator_category  iterator_category;

        /// CONSTRUCTORS
        RE_Iterator() : _base_iterator() {}
        explicit RE_Iterator(iterator_type iter = nullptr) : _base_iterator(iter) {}

        template <class U>
        RE_Iterator(const RE_Iterator<U>& other) : _base_iterator(other.base()) {}

        /// DESTRUCTOR
        virtual ~RE_Iterator() {}

        /// OPERATORS
        iterator_type base() const {
            return (_base_iterator);
        }

        RE_Iterator& operator++ () {
            --_base_iterator;
            return *this;
        }

        RE_Iterator operator++ (int) {
            RE_Iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        RE_Iterator operator+ (difference_type n) const {
            return RE_Iterator(_base_iterator - n);
        }

        RE_Iterator operator+= (difference_type n) {
            _base_iterator -= n;
            return *this;
        }


        RE_Iterator& operator-- () {
            ++_base_iterator;
            return *this;
        }

        RE_Iterator operator-- (int) {
            RE_Iterator tmp(*this);
            --(*this);
            return tmp;
        }

        RE_Iterator operator- (difference_type n) const {
            return RE_Iterator(_base_iterator + n);
        }

        RE_Iterator operator-= (difference_type n) {
            _base_iterator += n;
            return *this;
        }

        reference operator* () const {
            iterator_type tmp = _base_iterator;
            return *(--tmp);
        }

        pointer operator-> () const {
            return &(operator*());
        }

        reference operator[] (difference_type n) const {
            return (this->base()[-n - 1]);
        }
    };

    template <class Iterator1, class Iterator2>
    bool operator== (const RE_Iterator<Iterator1>& a, const RE_Iterator<Iterator2>& b) {
        return a.base() == b.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator!= (const RE_Iterator<Iterator1>& a, const RE_Iterator<Iterator2>& b) {
        return !(a == b);
    }

    template <class Iterator1, class Iterator2>
    bool operator< (const RE_Iterator<Iterator1>& a, const RE_Iterator<Iterator2>& b) {
        return a.base() > b.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator<= (const RE_Iterator<Iterator1>& a, const RE_Iterator<Iterator2>& b) {
        return a < b || a == b;
    }

    template <class Iterator1, class Iterator2>
    bool operator> (const RE_Iterator<Iterator1>& a, const RE_Iterator<Iterator2>& b) {
        return a.base() < b.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator>= (const RE_Iterator<Iterator1>& a, const RE_Iterator<Iterator2>& b) {
        return a > b || a == b;
    }

    template <class Iterator>
    typename RE_Iterator<Iterator>::difference_type operator- (const RE_Iterator<Iterator>& a, const RE_Iterator<Iterator>& b) {
        return a.base() - b.base();
    }

    template <class Iterator1, class Iterator2>
    typename RE_Iterator<Iterator1>::difference_type operator- (const RE_Iterator<Iterator1>& a, const RE_Iterator<Iterator2>& b) {
        return a.base() - b.base();
    }

    template <class Iterator>
    RE_Iterator<Iterator> operator+ (typename RE_Iterator<Iterator>::difference_type n, const RE_Iterator<Iterator>& iter) {
        return RE_Iterator<Iterator>(iter + n);
    }
}