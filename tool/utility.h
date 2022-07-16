#ifndef MYSTL_UTILITY_H
#define MYSTL_UTILITY_H

#include "type_traits.h"

namespace MySTL {
    // forward
    template< class _T >
    constexpr _T&& 
    forward(typename MySTL::remove_reference<_T>::type & t) noexcept {   
        return static_cast<_T&&>(t); 
    }
    template< class _T >
    constexpr _T&& 
    forward(typename MySTL::remove_reference<_T>::type && t) noexcept {
        return static_cast<_T&&>(t); 
    }
}
#endif
