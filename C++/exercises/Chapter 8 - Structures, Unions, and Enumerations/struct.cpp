#include <iostream>

struct integrals
{
    long double ld;
    double d;
    long l;
    int i;
    char c;
    bool b;
};

int main()
{
    std::cout << sizeof(long double) << '\n'
              << sizeof(double) << '\n'
              << sizeof(long) << '\n'
              << sizeof(int) << '\n'
              << sizeof(char) << '\n'
              << sizeof(bool) << '\n';
    return 0;
}