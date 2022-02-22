#ifndef STRING_EXERCISE_H
#define STRING_EXERCISE_H

#include <iostream>

namespace simple_string
{
    class String;
    char *expand(const char *ptr, int n);
    
    String &operator+=(String &a, const String &b);
    String &operator+(String &a, String &b);
    
    std::ostream &operator<<(std::ostream &os, const String &s);
    std::istream &operator>>(std::istream &is, String &s);
}

class String
{
    public:
        String(); // default constructor x{""}
        explicit String(const char *p); // constructor from C-style string
        
        String(const String &s); // copy constructor
        String &operator=(const String& s); // copy assignment
        String(String &&s) // move constructor
        String &operator=(String &&s) // move assignement
        
        ~String() // destructor
        
        char &operator[](int n); // unchecked element access
        const char operator[](int n) const;
        char &at(int n); // checked element access
        const char at(int n) const;
        
        String &operator+=(char c) // add char c to the end
        
        const char *c_str(); // c-style string access
        const char *c_str() const;
        
        int size() const; // number of elements
        int capacity() const; // elements plus available space
    
    private:
        static const short short_max = 15;
        int sz; // not including null char
        char *ptr;
        union
        {
            int space; // unused allocated space
            char ch[short_max+1]; // leave space for terminating 0
        };
        
        void check(int n) const; // range check
        void copy_from(const String &x);
        void move_from(String &x);
}

#endif