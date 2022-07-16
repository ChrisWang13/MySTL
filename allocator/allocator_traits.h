#ifndef MYSTL_ALLOCATOR_TRAIT_H
#define MYSTL_ALLOCATOR_TRAIT_H

#include <new>
#include "allocator.h"
#include "memory.h"

namespace MySTL {
    // allocator_trait
    template < class _Alloc >
    struct allocator_traits {
        typedef _Alloc                      allocator_type;
        typedef typename _Alloc::value_type value_type;
        typedef typename _Alloc::size_type  size_type;
        typedef value_type*                 pointer;
        // all member functions are static.
        static constexpr pointer 
        allocate(_Alloc& a, size_type n) {
            pointer ptr = a.allocate(n);
            return ptr;
        }
        static constexpr void 
        deallocate(_Alloc& a, pointer p, size_type n) {
            a.deallocate(p, n);
        }
        template< class _T, class... Args >
        static constexpr void 
        construct(_Alloc& a, _T* p, Args&&... args) {
            MySTL::construct_at(p, MySTL::forward(args)...); 
        }
        template< class _T >
        static constexpr void 
        destroy(_Alloc& a, _T* p) {
            MySTL::destroy_at(p);
        }
    };
} // namespace MySTL
#endif


