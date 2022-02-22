#include "unique-pointer.hpp"

using namespace smart_ptr::unique_ptr;

// default constructor
unique_ptr()
    : data{nullptr}
{
}

// constructor from pointer
template<typename T>
unique_ptr(T *val)
    : data{val}
{
}

// copy constructor
template <typename T>
unique_ptr(const unique_ptr &p);
    : data{new T}
{
    memcpy(data, p.data, sizeof(p.data);
}

// move constructor
template <typename T>
unique_ptr(unique_ptr