#include <iostream>
#include <random>
#include <vector>
#include <chrono>

// Include custom allocators
#include "myallocator_1.h"


using namespace std;

// Global variable declaration
extern unsigned int all;

// Alias for a 2D point represented by a pair of integers
using Point2D = std::pair<int, int>;

// Constants for test sizes
const int TestSize = 10000;
const int PickSize = 1000;

// Template function to test vector operations using different allocators
template <template <class T> class MyAllocator>
void test()
{
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);

    // Vector creation using custom allocator
    using IntVec = std::vector<int, MyAllocator<int>>;
    std::vector<IntVec, MyAllocator<IntVec>> vecints(TestSize);
    for (int i = 0; i < TestSize; i++)
        vecints[i].resize(dis(gen));

    using PointVec = std::vector<Point2D, MyAllocator<Point2D>>;
    std::vector<PointVec, MyAllocator<PointVec>> vecpts(TestSize);
    for (int i = 0; i < TestSize; i++)
        vecpts[i].resize(dis(gen));

    // Vector resize operations
    for (int i = 0; i < PickSize; i++)
    {
        int idx = dis(gen) - 1;
        int size = dis(gen);
        vecints[idx].resize(size);
        vecpts[idx].resize(size);
    }

    // Vector element assignment operations
    {
        int val = 10;
        int idx1 = dis(gen) - 1;
        int idx2 = vecints[idx1].size() / 2;
        vecints[idx1][idx2] = val;

        // Check if the assignment is correct
        if (vecints[idx1][idx2] == val)
            std::cout << "correct assignment in vecints: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecints: " << idx1 << std::endl;
    }
    {
        Point2D val(11, 15);
        int idx1 = dis(gen) - 1;
        int idx2 = vecpts[idx1].size() / 2;
        vecpts[idx1][idx2] = val;

        // Check if the assignment is correct
        if (vecpts[idx1][idx2] == val)
            std::cout << "correct assignment in vecpts: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecpts: " << idx1 << std::endl;
    }
}

int main()
{
    cout << "--------------------std::allocator--------------------" << endl;

    // Test with std::allocator
    auto start = chrono::system_clock::now();
    test<std::allocator>();
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Using Time = " << double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den << "s" << endl;

    
    cout << "-------------myallocator_1 with memory pool-------------" << endl;

    // Test with myallocator_1
    start = chrono::system_clock::now();
    test<myallocator_1>();
    end = chrono::system_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Using Time = " << double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den << "s" << endl;

   

    return 0;
}
