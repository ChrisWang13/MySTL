#pragma once 
#include <cstddef>
// <cstddef> for ptrdiff_t, defined as 
// typedef /*implementation-defined*/ ptrdiff_t, which stands for
// signed integer type returned when subtracting two pointers.

namespace MySTL {
    // "?_iterator_tag" serves as temporary object for marking iterator type.
    // using struct here for template argument "_Category".
    struct input_iterator_tag {};  
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    // MySTL::iterator
    template < class _Category, class _T, class _Distance = std::ptrdiff_t,
               class _Pointer = _T*, class _Reference = _T& >
    // use struct for public inheritance.
    // Example:
    // template < class T >
    // struct ?_iterator : public MySTL::iterator<MySTL::bidirectional_iterator_tag, T> {}
    struct iterator {
        typedef _Category    iterator_category;
        typedef _T           value_type;
        typedef _Distance    difference_type;
        typedef _Pointer     pointer;
        typedef _Reference   reference;
    };
    
    template< class _Iterator >
    struct iterator_traits {
        // typedef is defining a new type for use,
        // typename for value_type is a type and 
        // not a static member of _Iterator.
        typedef typename _Iterator::iterator_category iterator_category;
        typedef typename _Iterator::value_type        value_type;
        typedef typename _Iterator::difference_type   difference_type;
        typedef typename _Iterator::pointer           pointer;
        typedef typename _Iterator::reference         reference;
    };
 
    // partial specialization for raw pointer as random access iterator.
    // Example: sort(arr, arr + size);
    // remove const pointer types in C++20.
    template< class _T >
    struct iterator_traits<_T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef _T                         value_type;
        typedef std::ptrdiff_t             difference_type;
        typedef _T*                        pointer;
        typedef _T&                        reference;
    };
    
    
    template< class _Iterator >
    inline constexpr typename iterator_traits<_Iterator>::iterator_category
    iterator_category(const _Iterator&) { 
        // return required struct iterator tag
        return typename iterator_traits<_Iterator>::iterator_category(); 
    }

/******************************************************************************/
    // Iterator function: 
    // function template auto deduction.
    // 1. distance_helper() wraps up as distance()
    // 2. advance_helper() wraps up as advance()
    // 3. next() calls advance(), but leave itertor value unchanged
    // 3. prev() calls advance(), but leave itertor value unchanged
/******************************************************************************/
    template < class _InputIter >
    inline constexpr 
    typename iterator_traits<_InputIter>::difference_type 
    distance_helper(_InputIter first, _InputIter last, input_iterator_tag) {
        typename iterator_traits<_InputIter>::difference_type len = 0;
        while(first != last) {
            ++first;
            ++len;
        }
        return len;
    } 
    
    template < class _RandomAccessIter >
    inline constexpr 
    typename iterator_traits< _RandomAccessIter>::difference_type 
    distance_helper(_RandomAccessIter first, _RandomAccessIter last, random_access_iterator_tag) {
        return last - first;
    } 

    template < class _Iter >
    inline constexpr 
    typename iterator_traits<_Iter>::difference_type 
    distance(_Iter first, _Iter second) {
        return distance_helper(first, second, iterator_category(first));
    } 

    template < class _InputIter, class _Distance >
    inline constexpr void 
    advance_helper(_InputIter& i, _Distance n, input_iterator_tag) {
        for(; n >= 1; --n) {
            ++i;
        }  
    }
    
    template < class _BidirectionalIter, class _Distance >
    inline constexpr void 
    advance_helper(_BidirectionalIter& i, _Distance n, bidirectional_iterator_tag) {
        if(n > 0) {
            for(; n >= 1; --n) ++i;
        }
        else if(n < 0) {
            for(; n <= -1; ++n) --i;
        }
    }

    template < class _RandomAccessIter, class _Distance >
    inline constexpr void 
    advance_helper(_RandomAccessIter& i, _Distance n, random_access_iterator_tag) {
        i += n; 
    }
    
    template < class _Iterator, class _Distance >
    inline constexpr void 
    advance(_Iterator& i, _Distance n) {
        advance_helper(i, n, iterator_category(i));
    }

    template < class _InputIter >
    inline constexpr _InputIter
    next(_InputIter i, typename iterator_traits<_InputIter>::difference_type len = 1) {
        advance(i, len);
        return i;
    }

    template < class _BidirectionalIterator >
    inline constexpr _BidirectionalIterator
    prev(_BidirectionalIterator i, typename iterator_traits<_BidirectionalIterator>::difference_type len = 1) {
        advance(i, -len);
        return i;
    }
}
   