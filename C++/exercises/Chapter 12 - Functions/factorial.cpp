#include <iostream>
#include <cstdint>

std::uintmax_t factorial(int x)
{
    for (int i = x-1; i > 0; --i)
        x *= i;
    return x;
}

int main()
{
    int x;
    std::cout << "Input a number to find it's factorial." << std::endl;
    std::cin >> x;
    std::cout << x << "! = " << factorial(x) << std::endl;
    return 0;
}