#pragma once

#include "Iterator_traits.hpp"
#include "BD_Iterator.hpp"
#include "RE_Iterator.hpp"
#include "Utility.hpp"
#include "RB_Tree.hpp"

namespace ft {
    template<class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
    class set {
    public:
        typedef Key                                                 key_type;
        typedef Key                                                 value_type;
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
            friend class set;
        protected:
            key_compare comp;
            value_compare(key_compare c) : comp(c) {}
        public:
            bool operator() (const value_type& x, const value_type& y) const {
                return comp(x, y);
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
        explicit set (const Compare& comp = Compare(), const allocator_type& alloc = tree_allocator_type()) :
                _alloc(alloc), _compare(comp) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree);
        }

        // range
        template <class Iterator>
        set (Iterator first, Iterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) :
                _alloc(alloc), _compare(comp) {
            _tree = _tree_alloc.allocate(sizeof(tree_type));
            _tree_alloc.construct(_tree);
            for (; first != last; ++first)
                insert(*first);
        }

        // copy
        set (const set& other) : _alloc(other._alloc), _compare(other._compare) {
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
        ~set() {
            clear();
            _tree_alloc.destroy(_tree);
            _tree_alloc.deallocate(_tree, sizeof(tree_type));
        }

        /// Operator=
        set& operator= (const set& other) {
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

        /// Modifiers
        // insert - single element
        pair<iterator, bool> insert (const value_type& n) {
            node<value_type>* tmp = find(n).base();

            bool search_result = 0;
            if (tmp->NIL) {
                _tree->insert_node_set(n, _tree->root, _compare);
                tmp = find(n).base();
                search_result = 1;
            }
            return pair<iterator, bool>(iterator(tmp), search_result);
        }

        // insert - with hint
        iterator insert (iterator, const value_type& n) {
            node<value_type>* tmp = find(n).base();
            if (tmp->NIL)
                insert(n);
            return iterator(find(n).base());
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

        void swap (set& other) {
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
                if (key == *current->key_value)
                    return (current);
                else
                    current = _compare(key, *current->key_value) ? current->left : current->right;
            }
            return end();
        }

        const_iterator find (const key_type& key) const {
            node<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == *current->key_value)
                    return (current);
                else
                    current = _compare(key, *current->key_value) ? current->left : current->right;
            }
            return end();
        }

        size_type count (const key_type& key) const {
            return (find(key) == end()) ? 0 : 1;
        }

        iterator lower_bound (const key_type& key) {
            node<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == *current->key_value)
                    return iterator(current);
                else {
                    if (_compare(key, *current->key_value)) {
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
                if (key == *current->key_value)
                    return const_iterator(current);
                else {
                    if (_compare(key, *current->key_value)) {
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

            return (tmp == end()) ? tmp : (_compare(key, *tmp)) ? tmp : ++tmp;
        }

        const_iterator upper_bound (const key_type& key) const {
            const_iterator tmp = lower_bound(key);

            return (tmp == end()) ? tmp : (_compare(key, *tmp)) ? tmp : ++tmp;
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
    template <class Key, class Compare, class Alloc>
    bool operator== ( const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class Compare, class Alloc>
    bool operator!= ( const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class Key, class Compare, class Alloc>
    bool operator< ( const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    };

    template <class Key, class Compare, class Alloc>
    bool operator<= ( const set<Key, Compare,Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return !(rhs < lhs);
    };

    template <class Key, class Compare, class Alloc>
    bool operator> ( const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return rhs < lhs;
    };

    template <class Key, class Compare, class Alloc>
    bool operator>= ( const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return !(lhs < rhs);
    };
} // ft

namespace std {

    template <class Key, class Compare, class A>
    void swap(ft::set<Key, Compare, A> &m1, ft::set<Key, Compare, A> &m2 ) {
        m1.swap(m2);
    }
}