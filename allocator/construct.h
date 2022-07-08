#pragma once

#include <new.h>

namespace MySTL {
    // placement new, construct objects in allocated storage.
    template <class _T>
    void 
    construct(_T* ptr) {
        ::new (ptr) _T;
    }    
    template <class _T, class _TypeValue>
    void 
    construct(_T* ptr, const _TypeValue value) {
        ::new (ptr) _T(value);
    }    
    template <class _T>
    struct allocator {
        typedef _T          value_type;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        constexpr allocator() noexcept;
        constexpr allocator(const allocator& other ) noexcept;
    };
}