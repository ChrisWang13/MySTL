#pragma once 
#include <cstddef>
// <cstddef> for ptrdiff_t, defined as 
// typedef /*implementation-defined*/ ptrdiff_t, which stands for
// signed integer type returned when subtracting two pointers.

namespace MySTL{
    // "?_iterator_tag" serves as temporary object for marking iterator type.
    struct input_iterator_tag {};  
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    // MySTL::iterator 
    template <class _Category, class _T, class _Distance = ptrdiff_t,
              class _Pointer = _T*, class _Reference = _T&>
    struct iterator {
        typedef _Category    iterator_category;
        typedef _T           value_type;
        typedef _Distance    difference_type;
        typedef _Pointer     pointer;
        typedef _Reference   reference;
    };
    
}