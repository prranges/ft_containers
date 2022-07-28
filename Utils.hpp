#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
    // Enable_if
    template <bool Condition, class T = void>
    struct enable_if {};

    //	Specialisation enable_if for true
    template <class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    // Is_integral
    template<class T, bool val>
    struct integral_constant {
        static const bool value = val;
        typedef T value_type;
        typedef integral_constant type;
        operator value_type() const { return value; }
    };

    template <class T> struct is_integral : public ft::integral_constant<T, false> {};
    template <> struct is_integral<bool> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<signed char> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned char> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<wchar_t> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char16_t> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<short> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned short> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<int> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned int> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long long> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long long> : public ft::integral_constant<bool, true> {};

    // Lexicographical comparison
    template <class Iterator1, class Iterator2>
    bool lexicographical_compare (Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1) return false;
            else if (*first1 < *first2) return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template <class Iterator1, class Iterator2, class Compare>
    bool lexicographical_compare (Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2, Compare comp)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || comp(*first2, *first1)) return false;
            else if (comp(*first1, *first2)) return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }
//    template<class Iterator1, class Iterator2>
//    bool lexicographical_compare(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2) {
//        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
//            if (*first1 < *first2) return true;
//            if (*first2 < *first1) return false;
//        }
//        return (first1 == last1) && (first2 != last2);
//    }
//
//    template<class Iterator1, class Iterator2, class Compare>
//    bool lexicographical_compare(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2, Compare comp) {
//        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
//            if (comp(*first1, *first2)) return true;
//            if (comp(*first2, *first1)) return false;
//        }
//        return (first1 == last1) && (first2 != last2);
//    }

    // equal
    template<class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        for ( ; first1 != last1; ++first1, ++first2) {
            if (!(*first1 == *first2)) return false;
        }
        return true;
    }

    template<class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate p)
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!p(*first1, *first2)) {
                return false;
            }
        }
        return true;
    }
}

#endif