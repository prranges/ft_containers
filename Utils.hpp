#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

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