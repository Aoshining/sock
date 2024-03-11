#include "Vector.h"

// Default constructor
template <class T>
Vector<T>::Vector()
{
    m_nSize = m_nCapacity = 0;  // Initialize size and capacity to zero
}

// Parameterized constructor
template <class T>
Vector<T>::Vector(int size)
{
    m_nSize = m_nCapacity = size;  // Initialize both size and capacity with the given size
    m_pElements = new T[m_nCapacity];  // Allocate memory for elements
}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector& r)
{
    m_pElements = new T[r.m_nCapacity];  // Allocate memory for elements
    m_nSize = r.m_nSize;  // Set size
    m_nCapacity = r.m_nCapacity;  // Set capacity
    for (int i = 0; i < m_nSize; i++)
        m_pElements[i] = r.m_pElements[i];  // Copy elements from the source vector
}

// Assignment operator
template<class T>
Vector<T>& Vector<T>::operator=(const Vector& r)
{
    if (this == &r)
        return *this;  // Self-assignment check
    if (m_nCapacity) delete[] m_pElements;  // Release existing memory
    m_pElements = new T[r.m_nCapacity];  // Allocate memory for elements
    m_nSize = r.m_nSize;  // Set size
    m_nCapacity = r.m_nCapacity;  // Set capacity
    for (int i = 0; i < m_nSize; i++)
        m_pElements[i] = r.m_pElements[i];  // Copy elements from the source vector
    return *this;
}

// Destructor
template <class T>
Vector<T>::~Vector()
{
    if (m_nCapacity) delete[] m_pElements;  // Release allocated memory
}

// Subscript operator
template <class T>
T& Vector<T>::operator[](int index)
{
    return m_pElements[index];  // Allow access to elements using subscript notation
}

// At method with bounds checking
template <class T>
T& Vector<T>::at(int index)
{
    if (index < 0 || index >= m_nSize)
        __throw_out_of_range_fmt(__N("Vector::range_check: n (which is %zu) >= this->size() (which is %zu)"), index, this->size());
    return m_pElements[index];  // Return element at the specified index
}

// Size method
template <class T>
int Vector<T>::size() const
{
    return m_nSize;  // Return the current size of the vector
}

// Inflate method to increase capacity
template <class T>
void Vector<T>::inflate()
{
    if (m_nCapacity)
    {
        Vector copy(*this);  // Create a copy of the current vector
        m_nCapacity *= 2;  // Double the capacity
        delete[] m_pElements;  // Release existing memory
        m_pElements = new T[m_nCapacity];  // Allocate new memory with increased capacity
        for (int i = 0; i < m_nSize; i++)
            m_pElements[i] = copy.m_pElements[i];  // Copy elements from the old vector
    }
    else
    {
        m_nCapacity = 1;  // Set initial capacity to 1 if the vector is empty
        m_pElements = new T[1];  // Allocate memory for one element
    }
}

// Push back method to add an element to the end
template <class T>
void Vector<T>::push_back(const T& x)
{
    if (m_nSize < m_nCapacity)
        m_pElements[m_nSize++] = x;  // Add element to the end if there is space
    else
    {
        inflate();  // Increase capacity if the vector is full
        m_pElements[m_nSize++] = x;  // Add the element to the end
    }
}

// Clear method to set size to zero
template <class T>
void Vector<T>::clear()
{
    m_nSize = 0;  // Set the size to zero
}

// Empty method to check if the vector is empty
template <class T>
bool Vector<T>::empty() const
{
    return (m_nSize == 0);  // Return true if the vector is empty, otherwise false
}
