#pragma once

namespace ft {
    template <class Key, class Value>
    struct pair {
        typedef Key		first_type;
        typedef Value	second_type;

        first_type		first;
        second_type		second;

        /// Constructors
        pair() : first(), second() {}

        pair(const first_type& a, const second_type& b) : first(a), second(b) {}

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
    };

    template <class T1, class T2>
    bool operator==(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class T1, class T2>
    bool operator!=(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<=(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>=(const pair <T1, T2>& lhs, const pair <T1, T2>& rhs) {
        return !(lhs < rhs);
    }

    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 a, T2 b) {
        return pair<T1, T2>(a, b);
    }
}