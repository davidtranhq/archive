#include <cstring>

#include "string.h"

using namespace simple_string;

char *expand(const char *ptr, int n)
    // expand ptr into free store
{
    char *p = new char[n];
    strcpy(p, ptr);
    return p;
}

void String::copy_from(const String &x)
    // make *this a copy of x
{
    if (x.sz <= short_max)
    {
        memcpy(this, &x, sizeof(x);
        ptr = ch;
    }
    else
    {
        ptr = expand(x.ptr, x.sz+1);
        sz = x.sz;
        space = 0;
    }
}

void String::move_from(String &x)
{
    if (x.sz <= short_max)
    {
        memcpy(this, &x, sizeof(x));
        ptr = ch;
    }
    else
    {
        ptr = x.ptr; // ptr will be freed
        sz = x.sz;
        space = x.space;
        x.ptr = x.ch; // x = ""
        x.sz = 0;
        x.ch[0] = 0;
    }
}

String::String()
    : sz{0}, ptr{ch} // ch is initial location
{
    ch[0] = 0; // terminating 0
}

// constructor from c-style string
explicit String::String(const char *p)
    : sz{strlen(p)},
      ptr{(sz <= short_max) ? ch : new char[sz+1]},
      space{0} // null-character if using ch
{
    strcpy(ptr, p);
}

// copy constructor
String::String(const String &s)
{
    copy_from(x);
}

// move constructor
String::String(String &&x)
{
    move_from(x);
}

// copy assignment
String &String::operator=(const String &x)
{
    if (this == &x) // check for self-assignment
        return *this;
    // keep reference to ptr if it points to a resource, it would otherwise be
    // lost from copy_from()
    char *p = (sz > short_max) ? ptr : 0;
    copy_from(x);
    delete[] p;
    return *this;
}

// move assignment
String &String::operator=(String &&x)
{
    if (this == &x)
        return *this;
    if (sz > short_max)
        delete[] ptr;
    move_from(x);
    return *this;
}

String &String::operator+=(char c)
{
    if (sz == short_max)
    {
        int n = sz*2+2 // double the allocation, +2 because of null char
        ptr = expand(ptr, n);
        space = n-sz-2;
    }
    else if (sz > short_max)
    {
        if (space == 0)
        {
            int n = sz*2+2;
            char *p = expand(ptr, n);
            delete[] ptr;
            ptr = p;
            space = n-sz-2;
        }
        else
        {
            --space;
        }
    }
    ptr[sz] = c;
    ptr[++sz] = 0;
    return *this;
}

// << operator overload
std::ostream &operator<<(std::ostream &os, const String &s)
{
    return os << s.c_str();
}

// >> operator overload
std::istream &operator>>(std::istream &is, String &s)
{
    s = ""; // clear the string
    is >> std::ws // skip whitespace
    char ch = ' ';
    while (is.get(ch) && !isspace(ch))
        s += ch;
    return is;
}
