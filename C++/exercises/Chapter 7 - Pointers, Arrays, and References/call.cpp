void f(char c)
{
}

void g(char &c)
{
}

void h(const char &c)
{
}

int main()
{
    char c = 'c';
    unsigned char uc = 'c';
    signed char sc = 'c';
    
    f('a'); // legal, a is a char
    // g('a'); // illegal, lvalue reference used with rvalue
    h('a'); // legal, temp variable created to hold 'a' to which lvalue ref refers to

    f(49); // legal, a char is at least 8-bit
    // g(49); // illegal, same reason as g('a')
    h(49); //legal, same reason as h('a');
    
    f(3300); // legal but overflow
    // g(3300);
    h(3300);
    
    f(c); // legal, c is a char
    g(c); // legal, c is an lvalue
    h(c); // 
    
    f(uc);
    g(uc);
    h(uc);
    
    f(sc);
    g(sc);
    h(sc);
    
    return 0;
}

/*

A  non-
const
lvalue  reference  refers  to  an  object,  to  which  the  user  of  the  reference  can
write.
•A
const
lvalue reference refers to a constant, which is immutable from the point of view of
the user of the reference.
•
An rvalue  reference  refers  to  a  temporary  object,  which  the  user  of  the  reference  can  (and
typically will) modify, assuming that the object will never be used again

*/