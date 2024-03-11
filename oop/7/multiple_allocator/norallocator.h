#ifndef _NORALLOCATOR_H
#define _NORALLOCATOR_H

#include <iostream>
#include <stdexcept>
#include <limits>
#include <atomic>

using namespace std;

// Class representing a simple allocator using malloc and free
class dirmalloc {
public:
    // Function to allocate memory using malloc
    static void *allocate(unsigned int n) {
        if (void *temp = malloc(n))
            return temp;
        throw bad_alloc();
    }

    // Function to deallocate memory using free
    template< class T >
    static void deallocate(T* p, unsigned int n) {
        free(p);
    }
};

// Allocator template class
template< class T >
struct norallocator {
public:
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef T        value_type;
    typedef true_type propagate_on_container_move_assignment;
    typedef true_type is_always_equal;

    // Default constructor
    norallocator() noexcept {};

    // Copy constructor
    constexpr norallocator(const norallocator &other) noexcept {};

    // Constructor from a related type
    template <class U>
    constexpr norallocator(const norallocator<U> &other) noexcept {};

    // Destructor
    ~norallocator(){};

    // Allocate memory
    constexpr T* allocate(size_t n) {
        // Check for potential overflow
        if (std::numeric_limits<size_t>::max() / sizeof(T) < n)
            throw bad_array_new_length();

        // Allocate memory using dirmalloc
        pointer mem = static_cast<pointer>(dirmalloc::allocate(n * sizeof(T)));
        return mem;
    }

    // Deallocate memory
    void deallocate(T* p, size_t n) {
        // Deallocate memory using dirmalloc
        dirmalloc::deallocate(p, n);
    }

    // Return the address of the referenced object
    pointer address(reference x) const noexcept {
        return &x;
    }

    // Return the const address of the referenced object
    const_pointer address(const_reference x) const noexcept {
        return &x;
    }

    // Destroy an object at the given address
    template< class U >
    void destroy(U* p) {
        p->~U();
    }

    // Construct an object at the given address using placement new
    template< class U, class... Args >
    void construct(U* p, Args&&... args) {
        ::new ((void *)p) U(std::forward<Args>(args)...);
    }
};

// Comparison operators for allocator instances
template< class T1, class T2 >
constexpr bool
operator==(const norallocator<T1>& lhs, const norallocator<T2>& rhs) noexcept {
    return true;
}

template< class T1, class T2 >
constexpr bool
operator!=(const norallocator<T1>& lhs, const norallocator<T2>& rhs) noexcept {
    return false;
}

#endif
