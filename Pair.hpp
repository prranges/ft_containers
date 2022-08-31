#pragma once

namespace ft {
    template <class Key, class Value>
    struct pair {
        typedef Key		first_type;
        typedef Value	second_type;

        first_type		first;
        second_type		second;

        /// Constructors
        pair() : first(Key()), second(Value()) {}
        pair(const Key& a, const Value& b) : first(a), second(b) {}

        template<class K, class V>
        pair(const pair<K, V>& other) : first(other.first), second(other.second) {}

        /// Destructor
        ~pair() {};

        /// Operator=
        pair &operator= (const pair &other) {
            first = other.first;
            second = other.second;
            return *this;
        }

        void swap(pair& p) {
            std::swap(first,  p.first);
            std::swap(second, p.second);
        }
    };

    template <class Key, class Value>
    bool operator==(const pair <Key, Value>& lhs, const pair <Key, Value>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class Key, class Value>
    bool operator!=(const pair <Key, Value>& lhs, const pair <Key, Value>& rhs) {
        return !(lhs == rhs);
    }

    template <class Key, class Value>
    bool operator<(const pair <Key, Value>& lhs, const pair <Key, Value>& rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class Key, class Value>
    bool operator<=(const pair <Key, Value>& lhs, const pair <Key, Value>& rhs) {
        return !(rhs < lhs);
    }

    template <class Key, class Value>
    bool operator>(const pair<Key, Value>& lhs, const pair <Key, Value>& rhs) {
        return rhs < lhs;
    }

    template <class Key, class Value>
    bool operator>=(const pair <Key, Value>& lhs, const pair <Key, Value>& rhs) {
        return !(lhs < rhs);
    }

    template <class Key, class Value>
    pair<Key, Value> make_pair(Key a, Value b) {
        return pair<Key, Value>(a, b);
    }
}