#ifndef RA_ITERATOR_HPP
#define RA_ITERATOR_HPP

#include "Iterator_traits.hpp"

namespace ft {
    template <class T> class RA_Iterator {
        public:
            typedef T                                                           iterator_type;
            typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
            typedef typename iterator_traits<iterator_type>::value_type         value_type;
            typedef typename iterator_traits<iterator_type>::pointer            pointer;
            typedef typename iterator_traits<iterator_type>::reference          reference;
            typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
        private:
            iterator_type _val;
        public:

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
                _val = & (* other);
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

            template <class Iterator1, class Iterator2>
            friend bool	operator== (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
                return a._val == b._val;
            }

            template <class Iterator1, class Iterator2>
            friend bool	operator!=(const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
                return !(a._val == b._val);
            }

            template <class Iterator1, class Iterator2>
            friend bool	operator< (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
                return a._val < b._val;
            }

            template <class Iterator1, class Iterator2>
            friend bool	operator<= (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
                return a._val < b._val || a._val == b._val;
            }

            template <class Iterator1, class Iterator2>
            friend bool	operator> (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
                return a._val > b._val;
            }

            template <class Iterator1, class Iterator2>
            friend bool	operator>= (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
                return a._val > b._val || a._val == b._val;
            }

            template <class Iterator>
            friend typename RA_Iterator<Iterator>::difference_type operator- (const RA_Iterator<Iterator>& a, const RA_Iterator<Iterator>& b) {
                return a._val - b._val;
            }

            template <class Iterator1, class Iterator2>
            friend typename RA_Iterator<Iterator1>::difference_type operator- (const RA_Iterator<Iterator1>& a, const RA_Iterator<Iterator2>& b) {
                return a._val - b._val;
            }
    };

    template <class Iterator>
    RA_Iterator<Iterator> operator+ (typename RA_Iterator<Iterator>::difference_type n, const RA_Iterator<Iterator>& iter) {
        return RA_Iterator<Iterator>(iter + n);
    }

}

#endif