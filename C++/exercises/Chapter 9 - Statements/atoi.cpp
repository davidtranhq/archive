#include <iostream>

int atoi(char *s)
{
    for (auto c : s)
    {
        std::cout << c;
    }
}

int main()
{
    atoi("123");
    return 0;
}