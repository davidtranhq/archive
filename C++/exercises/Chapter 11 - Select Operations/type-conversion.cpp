#include <iostream>
#include <limits>

int main()
{
    //static_assert(sizeof(int) == sizeof(double), "unexpected sizes");
    /* {}-construction doesn't allow int to double conversion, because if the size of 
        an int is the same as the size of a double, then such a conversion must lose information. */
    int x = std::numeric_limits<int>::max();
    std::cout << "Value of x:" << x << '\n';
    double d = x;
    std::cout << "Value of d (taken from x): " << d << '\n';
    int y = x;
    std::cout << "Value of x (reconverted): " << x << '\n';
    std::cout << "Does x stay the same?: " << ((x == y) ? "yes" : "false");
    return 0;
}