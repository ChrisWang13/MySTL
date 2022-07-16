#ifndef MYSTL_TYPE_TRAITS_H
#define MYSTL_TYPE_TRAITS_H

namespace MySTL {
    // remove_reference
    template< class T > 
    struct remove_reference { 
        typedef T type; 
    };
    template< class T > 
    struct remove_reference<T&> { 
        typedef T type; 
    };
    template< class T > 
    struct remove_reference<T&&> { 
        typedef T type; 
    };
} // namespace MySTL
#endif
