#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <iterator>
#include <vector>

namespace ft {
    template < class T, class Allocator = std::allocator<T> > class Vector {
        public:
            typedef T                                               value_type;
            typedef Allocator                                       allocator_type;
            typedef ptrdiff_t                                       difference_type;
            typedef size_t                                          size_type;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::pointer                pointer;
            typedef typename std::vector<T>::iterator               iterator;
            typedef typename std::vector<T>::const_iterator         const_iterator;
            typedef typename std::vector<T>::reverse_iterator       reverse_iterator;
            typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
//            typedef ... iterator;
//            typedef ... const_iterator;
//            typedef ... reverse_iterator;
//            typedef ... const_reverse_iterator;
        private:
            size_type       _size;
            size_type       _capacity;
            allocator_type  _alloc;
            pointer         _pointer;

        public:
            /// CONSTRUCTORS
            // default
            explicit Vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _pointer(0) {}

            // fill
            explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc) {
                _pointer = _alloc.allocate(n);
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_pointer + i, val);
            }

            // range
            template <class InputIterator> Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {}

            // copy
            Vector (const Vector& x) {
                *this = x;
            }

            /// DESTRUCTOR
            ~Vector() {
                clear();
                if(_capacity)
                    _alloc.deallocate(_pointer, _capacity);
            }

            /// OPERATOR=
            Vector& operator= (const Vector& x) {
                if (this != &x) {
                    clear();
                    this->_size = x._size;
                    if (_capacity && _size > _capacity) {
                        _alloc.deallocate(_pointer, _capacity);
                        _capacity = _size;
                        _pointer = _alloc.allocate(_capacity);
                    }
                    for (size_type i = 0; i < _size; i++)
                        _alloc.construct(_pointer + i, x[i]);
                }
                return *this;
            }


            /// ITERATORS
            iterator begin() {
                return iterator(_pointer);
            }

            iterator end() {
                return iterator(_pointer + _size);
            }

            reverse_iterator rbegin() {
                return reverse_iterator(end());
            }

            const_reverse_iterator rbegin() const {
                return const_reverse_iterator(end());
            }

            reverse_iterator rend() {
                return reverse_iterator(begin());
            }

            const_reverse_iterator rend() const {
                return const_reverse_iterator(begin());
            }

            /// CAPACITY
            size_type size() const {
                return _size;
            }

            size_type max_size() const {
                return _alloc.max_size();
            }

            void resize (size_type n, value_type val = value_type()) {}

            size_type capacity() const {
                return _capacity;
            }

            bool empty() const {
                return _size == 0;
            }

            void reserve (size_type n) {
                if (n > _capacity) {
                    pointer tmp;
                    try {
                        tmp = _alloc.allocate(n);
                    } catch (std::exception& e) {
                        throw std::length_error(e.what());
                    }
                    try {
                        for (size_type i = 0; i < _size; i++)
                            _alloc.construct(tmp + i, _pointer[i]);
                    } catch (std::exception& e) {
                        for (size_type i = 0; tmp + i != NULL && i < _size; i++)
                            _alloc.destroy(tmp + i);
                        _alloc.deallocate(tmp, n);
                    }
                    for(size_type i = 0; i < _size; i++)
                        _alloc.destroy(_pointer + i);
                    if(_capacity)
                        _alloc.deallocate(_pointer, _capacity);
                    _capacity = n;
                    _pointer = tmp;
                }
            }

            /// ELEMENT ACCESS
            reference operator[] (size_type n) {
                return *(_pointer + n);
            }

            const_reference operator[] (size_type n) const {
                return *(_pointer + n);
            }

            reference at (size_type n) {
                if(n >= _capacity)
                    throw std::out_of_range("vector");
                return *(_pointer + n);
            }

            const_reference at (size_type n) const {
                if(n >= _capacity)
                    throw std::out_of_range("vector");
                return *(_pointer + n);
            }

            reference front() {
                return *_pointer;
            }

            const_reference front() const {
                return *_pointer;
            }

            reference back() {
                return *(_pointer + _size - 1);
            }

            const_reference back() const {
                return *(_pointer + _size - 1);
            }

            /// MODIFIERS
            // assign - range
            template <class InputIterator> void assign (InputIterator first, InputIterator last) {}

            // assign - fill
            void assign (size_type n, const value_type& val) {}

            void push_back (const value_type& val) {
                if (_size == _capacity)
                    reserve(_size + 1);;
                _alloc.construct(_pointer + _size, val);
                _size++;
            }

            void pop_back() {
                _alloc.destroy(_pointer + _size - 1);
                _size--;
            }

            // insert - single element
            iterator insert (iterator position, const value_type& val) {}

            // insert -  fill
            void insert (iterator position, size_type n, const value_type& val) {}

            // insert -  range
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last) {}

            iterator erase (iterator position) {}
            iterator erase (iterator first, iterator last) {}

            void swap (Vector& x) {
                std::swap(this->_size, x._size);
                std::swap(this->_pointer, x._pointer);
                std::swap(this->_alloc, x._alloc);
                std::swap(this->_capacity, x._capacity);
            }

            void clear() {
                for (; _size; --_size)
                    _alloc.destroy(_pointer + _size);
            }

            /// ALLOCATOR
            allocator_type get_allocator() const {
                return _alloc;
            }
    };

    /// RELATIONAL OPERATORS
    template <class T, class Allocator>
    bool operator== (const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {}

    template <class T, class Allocator>
    bool operator!= (const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {}

    template <class T, class Allocator>
    bool operator<  (const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {}

    template <class T, class Allocator>
    bool operator<= (const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {}

    template <class T, class Allocator>
    bool operator>  (const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {}

    template <class T, class Allocator>
    bool operator>= (const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {}

    /// SWAP
    template <class T, class Alloc>
    void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y);
}

#endif