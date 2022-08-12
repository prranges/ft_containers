#pragma once

#include <utility>
#include "Iterator_traits.hpp"
#include "BD_Iterator.hpp"
#include "RE_Iterator.hpp"
#include "Utility.hpp"
#include "RB_Tree.hpp"

namespace ft {
    template<class Key, class T, class Compare = ft::less <Key>, class Alloc = std::allocator <std::pair<const Key, T> > >
    class map {
    public:
        typedef Key                                         key_type;
        typedef T                                           mapped_type;
        typedef std::pair<const key_type, mapped_type>      value_type;
        typedef Compare                                     key_compare;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

    private:
        class pair_compare {
        private:
            key_compare _compare;
        public:
            pair_compare(key_compare& compare) : _compare(compare) {}
            bool operator() (const value_type& x, const value_type& y) const {
                return (_compare(x.first, y.first));
            }
        };

    public:
        typedef pair_compare                                            value_compare;
        typedef ft::RB_Tree<T>                                          tree_type;
        typedef ft::BD_Iterator<T*>                                     iterator;
        typedef ft::BD_Iterator<const T*>                               const_iterator;
        typedef ft::RE_Iterator<iterator>			                    reverse_iterator;
        typedef	ft::RE_Iterator<const_iterator>	                        const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef difference_type                                         size_type;
    private:
        allocator_type  _alloc;
        tree_type       _tree;
        key_compare     _compare;
    public:
        /// Constructors
        // empty
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}
        // range
        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}
        // copy
        map (const map& x) {}

        /// Destructor
        ~map() {}

        /// Operator=
        map& operator= (const map& x) {}

        /// Iterators
//        iterator begin() { return _tree.begin(); }
//        const_iterator begin() const { return _tree.begin(); }
//        iterator end() { return _tree.end(); }
//        const_iterator end() const { return _tree.end(); }
//        reverse_iterator rbegin() { return _tree.rbegin(); }
//        const_reverse_iterator rbegin() const { return _tree.rbegin(); }
//        reverse_iterator rend() { return _tree.rend(); }
//        const_reverse_iterator rend() const { return _tree.rend(); }

        /// Capacity
        bool empty() const {}
        size_type size() const {}
        size_type max_size() const {}

        /// Element access
        mapped_type& operator[] (const key_type& k) {}

        /// Modifiers
        // insert - single element
        std::pair<iterator, bool> insert (const value_type& val) {}
        // insert - with hint
        iterator insert (iterator position, const value_type& val) {}
        // insert - range
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last) {}

        // erase (1)
        void erase (iterator position) {}
        // erase (2)
        size_type erase (const key_type& k) {}
        // erase (3)
        void erase (iterator first, iterator last) {}

        // swap
        void swap (map& x) {}

        // clear
        void clear() {}

        /// Observers
        key_compare key_comp() const {}
        value_compare value_comp() const {}

        /// Operations
        iterator find (const key_type& k) {}
        const_iterator find (const key_type& k) const {}
        size_type count (const key_type& k) const {}
        iterator lower_bound (const key_type& k) {}
        const_iterator lower_bound (const key_type& k) const {}
        iterator upper_bound (const key_type& k) {}
        const_iterator upper_bound (const key_type& k) const {}
        std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {}
        std::pair<iterator,iterator>             equal_range (const key_type& k) {}

        /// Allocator
        allocator_type get_allocator() const {}
    };
} // ft
