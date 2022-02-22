#include <iostream>

class X
{
    public:
        X() { std::cout << "Initialize!\n"; }
        ~X() { std::cout << "Clean up!\n"; }
};

X x;

int main()
{
    std::cout << "Hello, world!\n";
}

