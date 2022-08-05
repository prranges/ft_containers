#pragma once

#include "Iterator_traits.hpp"

namespace ft {
    template <class T>
    class BD_Iterator {
        typedef T                                                           iterator_type;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::value_type         value_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
    private:
        iterator_type _val;
    public:

    };
}