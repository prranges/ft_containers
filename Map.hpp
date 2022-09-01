#pragma once

#include <utility>
#include "Iterator_traits.hpp"
#include "BD_Iterator.hpp"
#include "RE_Iterator.hpp"
#include "Utility.hpp"
#include "RB_Tree.hpp"
#include "Pair.hpp"

namespace ft {
    template<class Key, class Value, class Compare = std::less <Key>, class Alloc = std::allocator <ft::pair<const Key, Value> > >
    class map {
    public:
        typedef Key                                                 key_type;
        typedef Value                                               mapped_type;
        typedef ft::pair<const Key, Value>                          value_type;
        typedef Compare                                             key_compare;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef typename allocator_type::size_type                  size_type;

        typedef BD_Iterator<node<value_type>*, value_type>			iterator;
        typedef BD_Iterator<const node<value_type>*, value_type>	const_iterator;
        typedef RE_Iterator<iterator>			                    reverse_iterator;
        typedef	RE_Iterator<const_iterator>	                        const_reverse_iterator;

        typedef typename allocator_type::template rebind<node<value_type> >::other		node_allocator_type;
        typedef typename allocator_type::template rebind<RB_Tree<value_type> >::other	tree_allocator_type;
        typedef RB_Tree<value_type>*                                                    tree_type;

        class value_compare : public std::binary_function<value_type, value_type, bool> {
            friend class map;
        protected:
            key_compare comp;
            value_compare(key_compare c) : comp(c) {}
        public:
            bool operator() (const value_type& x, const value_type& y) const {
                return (comp(x.first, y.first));
            }
        };

    private:
        allocator_type      _alloc;
        node_allocator_type _node_alloc;
        tree_allocator_type _tree_alloc;
        tree_type           _tree;
        key_compare         _compare;
    public:
        /// Constructors
//        // empty
//        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = tree_allocator_type()) :
//        _alloc(alloc), _compare(comp) {
//            _tree = _tree_alloc.allocate(sizeof(tree_type));
//            _tree_alloc.construct(_tree);
//        }
//
//        // range
//        template <class Iterator>
//        map (Iterator first, Iterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
//            _alloc(alloc), _compare(comp) {
//            _tree = _tree_alloc.allocate(sizeof(tree_type));
//            _tree_alloc.construct(_tree);
//            for (; first != last; ++first)
//                insert(*first);
//        }
//
//        // copy
//        map (map& other) : _alloc(other._alloc), _compare(other._compare) { /// const map& other
//            _tree = _tree_alloc.allocate(sizeof(tree_type));
//            _tree_alloc.construct(_tree, *(other._tree));
//            iterator first = other.begin();
//            iterator last = other.end();
//            for (; first != last; ++first)
//                insert(*first);
//        }

        map() {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree);
        }

        explicit map( const Compare& comp, const Alloc& alloc = Alloc()) : _compare(comp), _alloc(alloc) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree);
        }

        template <class InputIt>
        map(InputIt first, InputIt last,
        const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _alloc(alloc), _compare(comp) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree);
            for (; first != last; first++)
                insert(ft::make_pair(first->first, first->second));
        }

        map(const map &other) : _alloc(other._alloc), _compare(other._compare) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree, *(other._tree));
            fillTree(other._tree->root);
        }

        void fillTree(node<value_type> *t) {
            if (!t->left->NIL)
                fillTree(t->left);
            if (!t->NIL) insert(*t->key_value);
            if (!t->right->NIL)
                fillTree(t->right);
        }

        /// Destructor
        ~map() { clear(); }

        /// Operator=
        map& operator= (const map& other) {
            if (this != & other) {
                _compare = other._compare;
                _alloc = other._alloc;
                clear();
                insert(other.begin(), other.end());
            }
            return *this;
        }

        /// Iterators
        iterator begin() { return iterator (_tree->begin()); }
        const_iterator begin() const { return const_iterator (_tree->begin()); }
        iterator end() { return iterator(_tree->end()); }
        const_iterator end() const { return const_iterator(_tree->end()); }
        reverse_iterator rbegin() { return reverse_iterator(_tree->end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree->end()); }
        reverse_iterator rend() { return reverse_iterator(_tree->begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(_tree->begin()); }

        /// Capacity
        bool empty() const { return _tree->size() == 0; }
        size_type size() const { return _tree->size(); }
        size_type max_size() const { return _node_alloc.max_size(); }

        /// Element access
        mapped_type& operator[] (const key_type& k) {
            node<value_type>* tmp = _tree->search(k);
            if (tmp->NIL){
                _tree->insert_node(ft::make_pair(k, mapped_type()), 0);
                tmp = _tree->search(k);
            }
            return tmp->key_value->second;
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

        // insert - with hint
        iterator insert (iterator position, const value_type& n) {
            node<value_type>* tmp = _tree->search(n.first);

            if (tmp->NIL)
                insert(n);
            return iterator(_tree->search(n.first));
        }

        // insert - range
        template <class Iterator>
        void insert (Iterator first, Iterator last) {
            for (; first != last; ++first)
                insert(*first);
        }

        // erase (1)
        void erase (iterator position) {
            iterator tmp = position;
            _tree->delete_node(tmp.base());
        }

        // erase (2)
        size_type erase (const key_type& key) {
            node<value_type> *tmp = _tree->search(key);
            if (tmp->NIL == 0)
            {
                _tree->delete_node(tmp);
                return 1;
            }
            return 0;
        }

        // erase (3)
        void erase (iterator first, iterator last) {
            iterator tmp;

            for (; first != last ;) {
                tmp = first++;
                _tree->delete_node(tmp.base());
            }
        }

        // swap
        void swap (map& other) {
            std::swap(_tree, other._tree);
        }

        // clear
        void clear() {
            _tree->clear();
        }

        /// Observers
        key_compare key_comp() const {
            return _compare;
        }
        value_compare value_comp() const {
            return value_compare(key_comp());
        }

        /// Operations
        iterator find (const key_type& k) {
            key_type key = k;
            node<value_type>* tmp = _tree->search(key);
            if (tmp->NIL)
                return iterator();
            return iterator(tmp);
        }

        const_iterator find (const key_type& k) const {
            key_type key = k;
            return const_iterator(_tree->search(key));
        }

        size_type count (const key_type& key) const {
            return (find(key) == end()) ? 0 : 1;
        }

        iterator lower_bound (const key_type& key) {
            iterator last = end();
            for (iterator first = begin(); first != last; ++first){
                if (first->first >= key)
                    return first;
            }
            return last;
        }

        const_iterator lower_bound (const key_type& key) const {
            iterator last = end();
            for (iterator first = begin(); first != last; ++first){
                if (first->first >= key)
                    return const_iterator(first);
            }
            return const_iterator(last);
        }

        iterator upper_bound (const key_type& key) {
            iterator last = end();
            for (iterator first = begin(); first != last; ++first) {
                if (first->first > key)
                    return first;
            }
            return last;
        }

        const_iterator upper_bound (const key_type& key) const {
            iterator last = end();
            for (iterator first = begin(); first != last; ++first) {
                if (first->first > key)
                    return const_iterator(first);
            }
            return const_iterator(last);
        }

        pair<iterator,iterator> equal_range (const key_type& key) {
            return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

        pair<const_iterator,const_iterator> equal_range (const key_type& key) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
        }

        /// Allocator
        allocator_type get_allocator() const { return _alloc; }
    };

    /// Relational operators
    template <class Key, class T, class Compare, class Alloc>
    bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator< ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        return !(rhs < lhs);
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator> ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        return rhs < lhs;
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
        return !(lhs < rhs);
    };
} // ft

namespace std {

    template <class Key, class T, class Compare, class A>
    void swap(ft::map<Key, T, Compare, A> &m1, ft::map<Key, T, Compare, A> &m2 ) {
        m1.swap(m2);
    }
}