#pragma once

#include <utility>
#include "Iterator_traits.hpp"
#include "BD_Iterator.hpp"
#include "RE_Iterator.hpp"
#include "Utility.hpp"
#include "RB_Tree.hpp"

namespace ft {
    template<class Key, class Value, class Compare = ft::less <Key>, class Alloc = std::allocator <ft::pair<const Key, Value> > >
    class map {
    public:
        typedef Key                                     key_type;
        typedef Value                                   mapped_type;
        typedef pair<const Key, Value>                  value_type;
        typedef Compare                                 key_compare;
        typedef Alloc                                   allocator_type;
        typedef typename Alloc::reference               reference;
        typedef typename Alloc::const_reference         const_reference;
        typedef typename Alloc::size_type               size_type;
        typedef typename Alloc::difference_type         difference_type;
        typedef typename Alloc::pointer                 pointer;
        typedef typename Alloc::const_pointer           const_pointer;
        typedef BD_Iterator<node<value_type>* >          iterator; ///? *
        typedef BD_Iterator<const node<value_type>* >    const_iterator; ///? *
        typedef RE_Iterator<iterator>			        reverse_iterator;
        typedef	RE_Iterator<const_iterator>	            const_reverse_iterator;
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
        typedef pair_compare                                                            value_compare;
        typedef RB_Tree<value_type>*                                                    tree_type;
        typedef typename allocator_type::template rebind<node<value_type> >::other		node_allocator_type;
        typedef typename allocator_type::template rebind<RB_Tree<value_type> >::other	tree_allocator_type;

    private:
        allocator_type      _alloc;
        node_allocator_type _node_alloc;
        tree_allocator_type _tree_alloc;
        tree_type           _tree;
        key_compare         _compare;
    public:
        /// Constructors
        // empty
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = tree_allocator_type()) :
        _alloc(alloc), _compare(comp) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree);
        }
        // range
        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
        _alloc(alloc), _tree(first, last, comp, _alloc), _compare(comp) {}
        // copy
        map (const map& other) : _alloc(other._alloc), _compare(other._compare) {}

        /// Destructor
        ~map() {}

        /// Operator=
        map& operator= (const map& other) {
            if (this != &other) {
                _tree->clear();
                _compare = other._compare;
                _alloc = other._alloc;
                insert(other.begin(), other.end());
            }
            return *this;
        }

        /// Iterators
        iterator begin() { return iterator(_tree->begin()); }
        const_iterator begin() const { return iterator (_tree->begin()); }
        iterator end() { return iterator(_tree->end()); }
        const_iterator end() const { return const_iterator(_tree->end()); }
        reverse_iterator rbegin() { return reverse_iterator(_tree->end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree->end()); }
        reverse_iterator rend() { return reverse_iterator(_tree->begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(_tree->begin()); }

        /// Capacity
        bool empty() const { return _tree->tree_size == 0; }
        size_type size() const { return _tree->tree_size; }
        size_type max_size() const { return _alloc->max_size(); }

        /// Element access
        mapped_type& operator[] (const key_type& k) {

        }

        /// Modifiers
        // insert - single element
        pair<iterator, bool> insert (const value_type& n) {
           node<value_type>* tmp = _tree->search(n.first);

           bool search_result = 0;
           if (tmp->NIL) {
               _tree->insert_node(n, 0);
               tmp = _tree->search(n.first);
               search_result = 1;
           }
            return pair<iterator, bool>(iterator(tmp), search_result);
        }
//        // insert - with hint
//        iterator insert (iterator position, const value_type& n) {
//            node<value_type>* tmp = _tree->search(n->first);
//
//            key_type p = n.first;
//            if (tmp->NIL)
//                _tree->insert_node(position.base(), n);
//            return iterator(_tree->search(p));
//        }
//        // insert - range
//        template <class InputIterator>
//        void insert (InputIterator first, InputIterator last) {
//            for (; first != last; ++first)
//                insert(make_pair(first->first, first->second));
//        }


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
        pair<const_iterator,const_iterator> equal_range (const key_type& k) const {}
        pair<iterator,iterator>             equal_range (const key_type& k) {}

        /// Allocator
        allocator_type get_allocator() const {}
    };
} // ft
