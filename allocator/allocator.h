#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include <new>
#include <cstddef>

namespace MySTL {
    // allocator
    template < class _T >
    struct allocator {
        typedef _T          value_type;
        typedef std::size_t size_type;
        typedef ptrdiff_t   difference_type;
        // constructor, no visble effect.
        constexpr allocator() noexcept {}
        constexpr allocator(const allocator& other ) noexcept {}
        template< class U >
        constexpr allocator( const allocator<U>& other ) noexcept {}
        // trivial destructor (with constexpr) destroys the default allocator.
        constexpr ~allocator() {}
        // allocate storage, construct object in allocator_traits. 
        constexpr _T* allocate(size_type n);
        // deallocate storage, destroy object in allocator_traits. 
        constexpr void deallocate(_T* p, size_type n);
    };
    // allocate member function.
    template< class _T >
    constexpr _T* allocator<_T>::
    allocate(size_type n) {
        if (n == 0) {
            return nullptr;
        }
        else {
            return static_cast<_T*>(::operator new(n * sizeof(_T)));
        }
    }
    // deallocate member function.
    template< class _T >
    constexpr void allocator<_T>::
    deallocate(_T* p, size_type) {
        if (p == nullptr)
            return;
        ::operator delete(p);
    }
} // namespace MySTL
#endif
