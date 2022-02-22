#ifndef SMART_POINTER_H
#define SMART_POINTER_H

namespace smart_ptr
{
    class unique_ptr;
}

template <typename T>
class unique_ptr
{
    public:
        unique_ptr(); // default constructor
        explicit unique_ptr(T *val); // constructor
        unique_ptr(const unique_ptr &p); // copy constructor
        unique_ptr(unique_ptr &&p); // move constructor
        ~unique_ptr(); // destructor
        
        unique_ptr &operator=(const unique_ptr &p); // copy assignment
        unique_ptr &operator=(unique_ptr &&p); // move assignment
        
        
        
        T *operator->() const; // *dereference access
        T &operator*() const; // -> access
        
        explicit operator bool(); // explicit bool conversion
        
        T *release(); // give back ownership of data
        
    private:
        T *data;
};

#endif