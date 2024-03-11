#ifndef _MYALLOCATOR_2_H
#define _MYALLOCATOR_2_H

#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

const int POOL = 32768;
const int BLOCK = 32;
const int NUM_BLOCK = 1024;

// Structure representing a block in the memory pool
struct block {
    char empty_or_full[1];  // Flag indicating whether the block is empty or full
    int blocksize;          // Size of the block
};

// Forward declaration of blockhead and its alias nextblock
struct blockhead;
typedef blockhead* nextblock;

// Structure representing the head of a memory pool block
struct blockhead {
    nextblock next;  // Pointer to the next block in the pool
};

// Class representing a memory pool allocator
class memorypool_2 {
public:
    static nextblock head;  // Static member variable representing the head of the memory pool

    // Function to allocate memory from the memory pool
    static void* allocate(size_t n) {
        if (n > POOL - 32) {
            // If the requested size is larger than the pool, use regular malloc
            if (void* temp = malloc(n))
                return temp;
            throw bad_alloc();
        }

        int blocknumber = n / BLOCK + 1;

        if (head == nullptr) {
            // If the memory pool is empty, allocate a new block
            char* mem = (char*)malloc(sizeof(struct blockhead) + POOL);
            head = (nextblock)mem;
            head->next = nullptr;
            mem = mem + sizeof(struct blockhead);
            block* t = (block*)mem;
            t->empty_or_full[0] = '0';
            t->blocksize = NUM_BLOCK - 1;
        }

        nextblock temp = head, pretemp = head;

        // Iterate through the blocks in the memory pool
        while (temp != nullptr) {
            char* start = (char*)temp + sizeof(struct blockhead);
            block* ss = (block*)start;
            int bsize = 0;

            // Iterate through the blocks within a blockhead
            while (1) {
                if (ss->empty_or_full[0] == '0' && ss->blocksize >= blocknumber) {
                    // If an empty block is found, allocate memory from it
                    void* return_memory = static_cast<void*>((char*)ss + BLOCK);
                    ss->empty_or_full[0] = '1';
                    block* sst = ss;

                    // Split the block if necessary
                    if (ss->blocksize - blocknumber != 0) {
                        int prsize = ss->blocksize;
                        ss = (block*)((char*)ss + BLOCK + blocknumber * BLOCK);
                        ss->empty_or_full[0] = '0';
                        ss->blocksize = prsize - blocknumber - 1;
                    }
                    sst->blocksize = blocknumber;
                    return return_memory;
                } else {
                    bsize = bsize + ss->blocksize + 1;
                    if (bsize >= NUM_BLOCK)
                        break;
                    ss = (block*)((char*)ss + (ss->blocksize + 1) * BLOCK);
                }
            }
            pretemp = temp;
            temp = temp->next;
        }

        // If no suitable block is found, allocate a new block
        char* mem = (char*)malloc(sizeof(struct blockhead) + POOL);
        nextblock tmem = (nextblock)mem;
        pretemp->next = tmem;
        tmem->next = nullptr;
        mem = mem + sizeof(struct blockhead);
        block* t = (block*)mem;
        t->empty_or_full[0] = '0';
        t->blocksize = NUM_BLOCK - 1;
        void* return_memory = static_cast<void*>(mem + BLOCK);
        t->empty_or_full[0] = '1';
        block* ttt = t;

        // Split the block if necessary
        if (t->blocksize - blocknumber > 0) {
            int prsize = t->blocksize;
            t = (block*)((char*)t + BLOCK + blocknumber * BLOCK);
            t->empty_or_full[0] = '0';
            t->blocksize = prsize - blocknumber - 1;
        }
        ttt->blocksize = blocknumber;
        return return_memory;
    }

    // Function to deallocate memory back to the memory pool
    static void deallocate(void* p, size_t n) {
        if (n > POOL - 32) {
            // If the size is larger than the pool, use regular free
            free(p);
        } else {
            nextblock temp = head;

            // Find the block to which the memory belongs
            while (temp != nullptr) {
                if (p >= static_cast<void*>(temp) && p < static_cast<void*>(temp->next)) {
                    break;
                }
                temp = temp->next;
            }

            if (temp == nullptr)
                return;

            block* mem = (block*)((char*)temp + sizeof(struct blockhead));
            block* tm = mem;

            // Iterate through the blocks within the blockhead
            while (((char*)tm + BLOCK) != p) {
                mem = tm;
                if (mem->blocksize < 0)
                    return;
                tm = (block*)((char*)tm + (1 + mem->blocksize) * BLOCK);
            }

            // Mark the block as empty
            tm->empty_or_full[0] = '0';

            // Merge adjacent empty blocks if possible
            if (tm == mem) {
                if ((block*)((char*)tm + (1 + tm->blocksize) * BLOCK) <= static_cast<void*>((char*)temp + sizeof(struct blockhead) + POOL)) {
                    block* tn = (block*)((char*)tm + (1 + tm->blocksize) * BLOCK);
                    if (tn->empty_or_full[0] == '0') {
                        tm->blocksize = tm->blocksize + tn->blocksize + 1;
                    }
                }
            } else {
                if ((block*)((char*)tm + (1 + tm->blocksize) * BLOCK) <= static_cast<void*>((char*)temp + sizeof(struct blockhead) + POOL)) {
                    block* tn = (block*)((char*)tm + (1 + tm->blocksize) * BLOCK);
                    if (mem->empty_or_full[0] == '1') {
                        if (tn->empty_or_full[0] == '0') {
                            tm->blocksize = tm->blocksize + tn->blocksize + 1;
                        }
                    } else {
                        if (tn->empty_or_full[0] == '0') {
                            mem->blocksize = mem->blocksize + tm->blocksize + tn->blocksize + 2;
                        } else {
                            mem->blocksize = mem->blocksize + tm->blocksize + 1;
                        }
                    }
                } else {
                    if (mem->empty_or_full[0] == '0') {
                        mem->blocksize = mem->blocksize + tm->blocksize + 1;
                    }
                }
            }
        }
    }
};

nextblock memorypool_2::head = nullptr;

// Allocator template class
template< class T >
struct myallocator_2 {
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
    myallocator_2() noexcept {};

    // Copy constructor
    constexpr myallocator_2(const myallocator_2 &other) noexcept {};

    // Constructor from a related type
    template <class U>
    constexpr myallocator_2(const myallocator_2<U> &other) noexcept {};

    // Destructor
    ~myallocator_2(){};

    // Allocate memory
    constexpr T* allocate(size_t n) {
        // Check for potential overflow
        if (std::numeric_limits<size_t>::max() / sizeof(T) < n)
            throw bad_array_new_length();

        // Allocate memory using memorypool_2
        pointer mem = static_cast<pointer>(memorypool_2::allocate(n * sizeof(T)));
        return mem;
    }

    // Deallocate memory
    void deallocate(T* p, size_t n) {
        memorypool_2::deallocate(p, n);
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
operator==(const myallocator_2<T1>& lhs, const myallocator_2<T2>& rhs) noexcept {
    return true;
}

template< class T1, class T2 >
constexpr bool
operator!=(const myallocator_2<T1>& lhs, const myallocator_2<T2>& rhs) noexcept {
    return false;
}

#endif
