#pragma once
#include "Iterator_traits.hpp"

namespace ft {
    template <class T> class RA_Iterator {
    private:
        T _val;
    public:
        typedef T                                               iterator_type;
        typedef typename iterator_traits<T>::difference_type    difference_type;
        typedef typename iterator_traits<T>::value_type         value_type;
        typedef typename iterator_traits<T>::pointer            pointer;
        typedef typename iterator_traits<T>::const_pointer      const_pointer;
        typedef typename iterator_traits<T>::reference          reference;
        typedef typename iterator_traits<T>::const_reference    const_reference;
        typedef typename iterator_traits<T>::iterator_category  iterator_category;

        /// CONSTRUCTORS
        RA_Iterator() : _val() {}
        explicit RA_Iterator(T val) : _val(val) {}
        RA_Iterator(const RA_Iterator& other) : _val(other._val) {}


        /// DESTRUCTOR
        virtual ~RA_Iterator() {}

        /// OPERATORS
        template <class Type>
        operator RA_Iterator<Type>() const {
            return RA_Iterator<Type>(_val);
        }

        template <class Iterator>
        RA_Iterator& operator= (RA_Iterator<Iterator> const & other) {
            _val = & (*other);
            return *this;
        }

        RA_Iterator& operator++ () {
            ++_val;
            return *this;
        }

        RA_Iterator operator++ (int) {
            RA_Iterator tmp(*this);
            ++_val;
            return tmp;
        }

        RA_Iterator operator+ (difference_type n) const {
            return RA_Iterator(_val + n);
        }

        RA_Iterator operator+= (difference_type n) {
            _val += n;
            return *this;
        }


        RA_Iterator& operator-- () {
            --_val;
            return *this;
        }

        RA_Iterator operator-- (int) {
            RA_Iterator tmp(*this);
            --_val;
            return tmp;
        }

        RA_Iterator operator- (difference_type n) const {
            return RA_Iterator(_val - n);
        }

        RA_Iterator operator-= (difference_type n) {
            _val -= n;
            return *this;
        }

        reference operator[] (difference_type n) const {
            return *(_val + n);
        }

        reference operator* () const {
            return *_val;
        }

        pointer operator-> () const {
            return _val;
        }

        iterator_type base() const { return _val; }
    };

    template <class Iterator1, class Iterator2>
    bool	operator== (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
        return a.base() == b.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator!=(const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
        return !(a.base() == b.base());
    }

    template <class Iterator1, class Iterator2>
    bool	operator< (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
        return a.base() < b.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator<= (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
        return a.base() < b.base() || a.base() == b.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator> (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
        return a.base() > b.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator>= (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
        return a.base() > b.base() || a.base() == b.base();
    }

    template <class Iterator>
    typename RA_Iterator<Iterator>::difference_type operator- (const RA_Iterator<Iterator>& a, const RA_Iterator<Iterator>& b) {
        return a.base() - b.base();
    }

    template <class Iterator1, class Iterator2>
    typename RA_Iterator<Iterator1>::difference_type operator- (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
        return a.base() - b.base();
    }

    template <class Iterator>
    RA_Iterator<Iterator> operator+ (typename RA_Iterator<Iterator>::difference_type n, const RA_Iterator<Iterator>& iter) {
        return RA_Iterator<Iterator>(iter + n);
    }
}