#ifndef _MYALLOCATOR_1_H
#define _MYALLOCATOR_1_H

#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

#define MAX 262144
#define BLOCK 256
#define NUM_OF_POOL MAX / BLOCK

// Union to represent the memory pool linked list nodes
union List {
    union List *next_pool;  // Pointer to the next node in the pool
    char not_empty[1];
};

// Class representing a memory pool allocator
class memorypool_1 {
private:
    static List* pool[NUM_OF_POOL];  // Array of linked lists for memory pools
    static char *start;  // Start of the memory pool
    static char *end;    // End of the memory pool
    static size_t total_size;  // Total size of allocated memory

    // Helper function to calculate the index of the memory pool for a given size
    inline static size_t poolindex(size_t n) {
        return (n + BLOCK - 1) / BLOCK - 1;
    }

    // Helper function to round up the size to the next multiple of BLOCK
    inline static size_t largen(size_t n) {
        if (n % BLOCK == 0)
            return n;
        else{
            size_t temp = n / BLOCK;
            return (temp + 1) * BLOCK;
        }
    }

    // Helper function to allocate memory from the pool
    static char *alloc(size_t size, int &blocknum);

    // Helper function to supplement the memory pool when it runs out of space
    static void *supplement(size_t n);

public:
    // Function to allocate memory from the pool
    static void *allocate(size_t n) {
        List**curpool;
        List *result;
        if (n > (size_t)MAX) {
            // If the requested size is larger than the maximum, use regular malloc
            void *temp = malloc(n);
            return temp;
        }
        curpool = pool + poolindex(n);
        result = *curpool;
        if (result == nullptr) {
            // If the pool is empty, supplement it with a new block of memory
            void *r = supplement(largen(n));
            return r;
        }
        *curpool = result->next_pool;
        return result;
    }

    // Function to deallocate memory back to the pool
    static void deallocate(void *p, size_t n) {
        List *q = (List *)p;
        List**curpool;
        if (n > (size_t)MAX) {
            // If the size is larger than the maximum, use regular free
            free(p);
            return;
        }
        curpool = pool + poolindex(n);
        q->next_pool = *curpool;
        *curpool = q;
    }
};

char *memorypool_1::start = nullptr;
char *memorypool_1::end = nullptr;
size_t memorypool_1::total_size = 0;
List* memorypool_1::pool[NUM_OF_POOL] = {nullptr};

char *memorypool_1::alloc(size_t n, int &blocknum) {
    char *result;
    size_t need = n * blocknum;
    size_t remain = end - start;

    if (remain >= need) {
        // If there is enough space in the current block, allocate from it
        result = start;
        start += need;
        return result;
    } else if (remain >= n) {
        // If there is enough space for at least one block, adjust blocknum
        blocknum = remain / n;
        need = n * blocknum;
        result = start;
        start += need;
        return result;
    } else {
        // If there is not enough space, supplement the memory pool with a new block
        size_t newsize = 2 * need + largen(total_size / 256);
        if (newsize > 0 && start != nullptr) {
            // Link the remaining space in the old block to the pool
            List**temp = pool + poolindex(remain);
            ((List *)start)->next_pool = *temp;
            *temp = (List *)start;
        }
        // Allocate a new block and update pointers
        start = (char *)malloc(newsize);
        total_size += newsize;
        end = start + newsize;
        return alloc(n, blocknum);
    }
}

void *memorypool_1::supplement(size_t n) {
    int blocknum = 20;
    char *chunk = alloc(n, blocknum);
    List**poollist;
    List *result;
    List *current_List, *next_List;

    if (blocknum == 1) return chunk;  // If only one block is needed, return the chunk
    poollist = pool + poolindex(n);
    result = (List *)chunk;
    *poollist = next_List = (List *)(chunk + n);
    int i = 1;
    #pragma simd
    while(1){
        current_List = next_List;
        next_List = (List *)((char *)next_List + n);
        if (blocknum - 1 == i) {
            // Link the last block in the chunk to nullptr
            current_List->next_pool = nullptr;
            break;
        } else {
            current_List->next_pool = next_List;
        }
        i++;
    }
    return result;
}

// Allocator template class
template< class T >
struct myallocator_1{
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

    myallocator_1() noexcept {};
    constexpr myallocator_1(const myallocator_1 &other) noexcept {};
    template <class U>
    constexpr myallocator_1(const myallocator_1<U> &other) noexcept {};
    ~myallocator_1(){};
    constexpr T* allocate( size_t n ){
        // Allocate memory from the memory pool
        if( std::numeric_limits< size_t >::max() / sizeof(T) < n)
            throw bad_array_new_length();
        pointer mem = static_cast<pointer>(memorypool_1::allocate(n * sizeof(T)));
        return mem;
    }
    void deallocate( T* p, size_t n ){
        // Deallocate memory back to the memory pool
        memorypool_1::deallocate(p, n);
    }
    pointer address( reference x ) const noexcept{
        // Return the address of the referenced object
        return &x;
    }
    const_pointer address( const_reference x ) const noexcept{
        // Return the const address of the referenced object
        return &x;
    }
    template< class U >
    void destroy( U* p ){
        // Destroy the object at the given address
        p->~U();
    }
    template< class U, class... Args >
    void construct( U* p, Args&&... args ){
        // Construct an object at the given address using placement new
        ::new ((void *)p) U(std::forward<Args>(args)...);
    }
};

// Comparison operators for allocator instances
template< class T1, class T2 >
constexpr bool
operator==( const myallocator_1<T1>& lhs, const myallocator_1<T2>& rhs ) noexcept
{
    return true;
}

template< class T1, class T2 >
constexpr bool
operator!=( const myallocator_1<T1>& lhs, const myallocator_1<T2>& rhs ) noexcept
{
    return false;
}

#endif
