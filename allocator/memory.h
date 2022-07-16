#ifndef MYSTL_MEMORY_H
#define MYSTL_MEMORY_H

#include "..\tool\utility.h"

namespace MySTL {
    // global funtion construct_at() in MySTL namespace.
    template < class _T, class... Args >
    constexpr _T* construct_at(_T* p, Args&&... args) {
        // placement new
        // 1.c 2.v 3.cv 4.non-cv (pointer argument which is passed in)
        // -> cv-qualifiers pointer -> remove qualifiers.
        return ::new (const_cast<void*>(static_cast<const volatile void*>(p)))
        _T(MySTL::forward<Args>(args)...);
    }
    // global funtion destroy_at() in MySTL namespace.
    // explict destruct (e.g., pop_back()): destruct last object in container, 
    // then decrease iterator last.
    // implicit destruct (e.g., destructor of container): destruct 
    // objects from iterator first to last.
    // UB to destruct an object twice.
    template< class _T >
    constexpr void destroy_at(_T* p) {
        // non-array type
        // This is used as internal function for destructing object.
        p->~_T(); 
    }
}

#endif
