#pragma once
#include "Utility.hpp"
#include "RA_Iterator.hpp"
#include "RE_Iterator.hpp"

namespace ft {
    template < class T, class Allocator = std::allocator<T> > class vector {
    public:
        typedef T                                               value_type;
        typedef Allocator                                       allocator_type;
        typedef typename allocator_type::difference_type        difference_type;
        typedef typename allocator_type::size_type              size_type;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename ft::RA_Iterator<T*>                    iterator;
        typedef typename ft::RA_Iterator<const T*>              const_iterator;
        typedef typename ft::RE_Iterator<iterator>              reverse_iterator;
        typedef typename ft::RE_Iterator<const_iterator>        const_reverse_iterator;

    private:
        size_type       _size;
        size_type       _capacity;
        allocator_type  _alloc;
        pointer         _pointer;

    public:
        /// CONSTRUCTORS
        // default
        explicit vector (const allocator_type& alloc = allocator_type()) :
            _size(0),
            _capacity(0),
            _alloc(alloc),
            _pointer(0) {}

        // fill
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
            if (n > this->max_size())
                throw (std::length_error("vector"));
            _alloc = alloc;
            _capacity = _size = n;
            _pointer = _alloc.allocate(_capacity);
            for (size_type i = 0; i < n; ++i)
                _alloc.construct(_pointer + i, val);
        }

        // range
        template <class Iterator> vector (Iterator first, Iterator last, const allocator_type& alloc = allocator_type(),
        typename ft::enable_if<!ft::is_integral<Iterator>::value, void>::type* = 0) :
            _size(0),
            _capacity(0),
            _alloc(alloc) {
            _pointer = _alloc.allocate(_capacity);
            this->assign(first, last);
        };

        // copy
        vector(const vector& other) : _size(other._size), _capacity(other._capacity), _pointer(0) {
            _alloc = other.get_allocator();
            _pointer = _alloc.allocate(other._capacity);
            for (size_t i = 0; i < _size; ++i)
                _pointer[i] = other._pointer[i];
        };

        /// DESTRUCTOR
        ~vector() {
            clear();
            _alloc.deallocate(_pointer, _capacity);
        }

        /// OPERATOR=
        vector& operator= (const vector& x) {
            if (this != &x) {
                clear();
                this->_size = x._size;
                if (_size > _capacity) {
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

        const_iterator begin() const {
            return const_iterator(_pointer);
        }

        iterator end() {
            return iterator(_pointer + _size);
        }

        const_iterator end() const {
            return const_iterator(_pointer);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin());
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

        void resize (size_type n, value_type val = value_type()) {
            if (n > this->max_size())
                throw (std::length_error("vector"));
            if (n < _size) {
                for(size_type i = n; i < _size; i++)
                    _alloc.destroy(_pointer + i);
                _size = n;
            }
            else if (n > _size) {
                if (_capacity < n)
                    this->reserve(_capacity * 2 > n ? _capacity * 2 : n);
                for (size_type i = _size; i < n; i++) {
                    _alloc.construct(_pointer + i, val);
                    _size++;
                }
            }
        }

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
                    for (size_type i = 0; i < _size; ++i)
                        _alloc.construct(tmp + i, _pointer[i]);
                } catch (std::exception& e) {
                    for (size_type i = 0; tmp + i != NULL && i < _size; ++i)
                        _alloc.destroy(tmp + i);
                    _alloc.deallocate(tmp, n);
                }
                for(size_type i = 0; i < _size; ++i)
                    _alloc.destroy(_pointer + i);
                if(_pointer)
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
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
            difference_type n = last - first;
            if (n < 0)
                throw std::length_error("vector");
            clear();
            reserve(n);
            for (; first != last; ++first) {
                this->push_back(*first);
            }
        };

        // assign - fill
        void assign (size_type n, const value_type& val) {
            clear();
            if (n > _capacity) {
                _alloc.deallocate(_pointer, _capacity);
                _pointer = _alloc.allocate(n);
                _capacity = n;
            }
            for (size_type i = 0; i < n; i++)
                _alloc.construct(_pointer + i, val);
            _size = n;
        }

        void push_back (const value_type& val) {
            if (_size == _capacity)
                reserve(_capacity ? _capacity * 2 : 1);
            _alloc.construct(_pointer + _size, val);
            ++_size;
        }

        void pop_back() {
            _alloc.destroy(_pointer + _size - 1);
            --_size;
        }

        // insert -  fill
        void insert( iterator position, size_type n, const value_type& val) {
            size_type dist = position - begin();
            size_type new_size = _size + n;
            if (n >= _capacity) {
                reserve(_capacity + n);
                _size = new_size;
            } else {
                for (; _size != new_size; ++_size) {
                    if (_size == _capacity)
                        reserve(_capacity * 2);
                }
            }
            for (size_type i = _size; i > 0; --i) {
                for (; n > 0 && i < dist + n && i >= dist; --n, --i) {
                    _pointer[i] = val;
                }
                _pointer[i] = _pointer[i - n];
            }
        };

        //insert - single element
        iterator insert (iterator position, const value_type& val) {
             size_t dist = position - begin();
             insert(position, 1, val);
             return iterator(_pointer + dist);
        }

        // insert -  range
        template <class Iterator>
        void insert (iterator position, Iterator first, Iterator last, typename ft::enable_if<!ft::is_integral<Iterator>::value>::type* = 0) {
            size_t range = last - first;
            pointer tmp_pointer = _alloc.allocate(range);
            bool result = true;
            size_t i = 0;
            for (;first != last; ++first, ++i) {
                try {
                    tmp_pointer[i] = *first;
                }
                catch (...) {
                    result = false; break;
                }
            }
            _alloc.deallocate(tmp_pointer, range);
            if (!result) {
                throw std::exception();
            }

            size_t dist = position - begin();
            size_t new_size = _size + range;
                if (range >= _capacity) {
                    reserve(_capacity + range);
                    _size = new_size;
                } else {
                    for (; _size != new_size; ++_size) {
                        if (_size == _capacity)
                            reserve(_capacity * 2);
                    }
                }
            for (size_t i = _size - 1; i >= 0; --i) {
                if (i == dist + range - 1) {
                    for (; range > 0; --range, --i) {
                        _pointer[i] = *--last;
                    }
                    return;
                }
                _pointer[i] = _pointer[i - range];
            }
        }

        // single element
        iterator erase(iterator position) {
            return erase(position, position + 1);
        }

        // range
        iterator erase( iterator first, iterator last ) {
            size_t start = first - begin();
            size_t end = last - begin();
            size_t offset = end - start;
            _size -= offset;
            for (size_t i = start; i < _size; ++i) {
                _pointer[i] = _pointer[i + offset];
            }
            return iterator(_pointer + start);
        }

        void swap(vector& other) {
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
            std::swap(_pointer, other._pointer);
            std::swap(_alloc, other._alloc);
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
    bool operator== (const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < rhs.size(); i++)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }

    template <class T, class Allocator>
    bool operator!= (const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
        return 	!(lhs == rhs);
    }

    template <class T, class Allocator>
    bool operator<  (const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
        if (lhs.size() < rhs.size()) return true;
        if (lhs.size() > rhs.size()) return false;

        for (size_t i = 0; i < lhs.size(); ++i) {
            if (lhs[i] == rhs[i]) { continue; }
            return lhs[i] < rhs[i];
        }
        return false;
    }

    template <class T, class Allocator>
    bool operator<= (const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Allocator>
    bool operator>  (const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
        return rhs < lhs;
    }

    template <class T, class Allocator>
    bool operator>= (const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
        return !(lhs < rhs);
    }
} // ft

namespace std{
    /// SWAP
    template< class T, class Alloc >
    void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
        lhs.swap(rhs);
    }
}