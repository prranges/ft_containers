#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft {

    /// TEMPLATE
    template <class Iterator> struct iterator_traits {
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::const_pointer        const_pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::reference            const_reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };

    // Specialization for pointer
    template <class T> struct iterator_traits<T*> {
        typedef ptrdiff_t                               difference_type;
        typedef T                                       value_type;
        typedef T*                                      pointer;
        typedef const T*                                const_pointer;
        typedef T&                                      reference;
        typedef const T&                                const_reference;
        typedef std::random_access_iterator_tag         iterator_category;
    };
}

#endif