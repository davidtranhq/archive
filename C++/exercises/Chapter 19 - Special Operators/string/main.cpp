#include <iostream>

#include "string.h"

using namespace simple_string;

int main()
{
    String s {"Hello"};
    std::cout << s << '\n';
    s += ',' += 'W' += 'o' += 'r' += 'l' += 'd' += '!';
    std::cout << s << '\n';
    
    String s2 {"Sweet"}
    return 0;
}