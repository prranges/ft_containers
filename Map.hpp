#pragma once

#include "Iterator_traits.hpp"
#include "BD_Iterator.hpp"
#include "RE_Iterator.hpp"
#include "Utility.hpp"
#include "RB_Tree.hpp"
#include "Pair.hpp"

namespace ft {
    template<class Key, class Value, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, Value> > >
    class map {
    public:
        typedef Key                                                 key_type;
        typedef Value                                               mapped_type;
        typedef pair<const Key, Value>                              value_type;
        typedef Compare                                             key_compare;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef typename allocator_type::size_type                  size_type;
        typedef typename allocator_type::difference_type			difference_type;

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
                return comp(x.first, y.first);
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
        // empty
        explicit map (const Compare& comp = Compare(), const allocator_type& alloc = tree_allocator_type()) :
        _alloc(alloc), _compare(comp) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree);
        }

        // range
        template <class Iterator>
        map (Iterator first, Iterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) :
            _alloc(alloc), _compare(comp) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree);
            for (; first != last; ++first)
                insert(*first);
        }

        // copy
        map (const map& other) : _alloc(other._alloc), _compare(other._compare) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree, *(other._tree));
            copy_nodes(other._tree->root);
        }

    private:
        void copy_nodes(node<value_type> *t) {
            if (!t->left->NIL)
                copy_nodes(t->left);
            if (!t->NIL) insert(*t->key_value);
            if (!t->right->NIL)
                copy_nodes(t->right);
        }

    public:

        /// Destructor
        ~map() {
            clear();
            _tree_alloc.destroy(_tree);
            _tree_alloc.deallocate(_tree, sizeof(tree_type));
        }

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
        iterator begin() {
            return iterator (_tree->begin());
        }

        const_iterator begin() const {
            return const_iterator (_tree->begin());
        }

        iterator end() {
            return iterator(_tree->end());
        }

        const_iterator end() const {
            return const_iterator(_tree->end());
        }

        reverse_iterator rbegin() {
            return reverse_iterator(_tree->end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(_tree->end());
        }

        reverse_iterator rend() {
            return reverse_iterator(_tree->begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(_tree->begin());
        }

        /// Capacity
        bool empty() const {
            return _tree->size() == 0;
        }

        size_type size() const {
            return _tree->size();
        }

        size_type max_size() const {
            return _node_alloc.max_size();
        }

        /// Element access
        mapped_type& operator[] (const key_type& k) {
            node<value_type>* tmp = find(k).base();
            if (tmp->NIL) {
                _tree->insert_node(ft::make_pair(k, mapped_type()), _tree->root, _compare);
                tmp = find(k).base();
            }
            return tmp->key_value->second;
        }

        /// Modifiers
        // insert - single element
        pair<iterator, bool> insert (const value_type& n) {
           node<value_type>* tmp = find(n.first).base();

           bool search_result = 0;
           if (tmp->NIL) {
               _tree->insert_node(n, _tree->root, _compare);
               tmp = find(n.first).base();
               search_result = 1;
           }
            return pair<iterator, bool>(iterator(tmp), search_result);
        }

        // insert - with hint
        iterator insert (iterator, const value_type& n) {
            node<value_type>* tmp = find(n.first).base();
            if (tmp->NIL)
                insert(n);
            return iterator(find(n.first).base());
        }

        // insert - range
        template <class Iterator>
        void insert (Iterator first, Iterator last) {
            for (; first != last; ++first)
                insert(*first);
        }

        // erase - position
        void erase (iterator position) {
            iterator tmp = position;
            _tree->delete_node(tmp.base());
        }

        // erase - key
        size_type erase (const key_type& key) {
            node<value_type> *tmp = find(key).base();
            if (!tmp->NIL) {
                _tree->delete_node(tmp);
                return 1;
            }
            return 0;
        }

        // erase - range
        void erase (iterator first, iterator last) {
            iterator tmp;

            for (; first != last ;) {
                tmp = first++;
                _tree->delete_node(tmp.base());
            }
        }

        void swap (map& other) {
            std::swap(_tree, other._tree);
        }

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
        iterator find (const key_type& key) {
            node<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == current->key_value->first)
                    return (current);
                else
                    current = _compare(key, current->key_value->first) ? current->left : current->right;
            }
            return end();
        }

        const_iterator find (const key_type& key) const {
            node<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == current->key_value->first)
                    return (current);
                else
                    current = _compare(key, current->key_value->first) ? current->left : current->right;
            }
            return end();
        }

        size_type count (const key_type& key) const {
            return (find(key) == end()) ? 0 : 1;
        }

        iterator lower_bound (const key_type& key) {
            node<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == current->key_value->first)
                    return iterator(current);
                else {
                    if (_compare(key, current->key_value->first)) {
                        if (!current->left->NIL)
                            current = current->left;
                        else
                            return iterator(current);
                    }
                    else {
                        if (!current->right->NIL)
                            current = current->right;
                        else
                            return ++iterator(current);
                    }
                }
            }
            return end();
        }

        const_iterator lower_bound (const key_type& key) const {
            node<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == current->key_value.first)
                    return const_iterator(current);
                else {
                    if (_compare(key, current->key_value.first)) {
                        if (!current->left->NIL)
                            current = current->left;
                        else
                            return const_iterator(current);
                    }
                    else {
                        if (!current->right->NIL)
                            current = current->right;
                        else
                            return ++const_iterator(current);
                    }
                }
            }
            return end();
        }

        iterator upper_bound (const key_type& key) {
            iterator tmp = lower_bound(key);

            return (tmp == end()) ? tmp : (_compare(key, tmp->first)) ? tmp : ++tmp;
        }

        const_iterator upper_bound (const key_type& key) const {
            const_iterator tmp = lower_bound(key);

            return (tmp == end()) ? tmp : (_compare(key, tmp->first)) ? tmp : ++tmp;
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