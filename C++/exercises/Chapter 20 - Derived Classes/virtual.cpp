#include <iostream>

struct A
{
    void f(int x) const
    {
        std::cout << "A: " << x << '\n';
    }
    virtual void g(double x)
    {
        std::cout << "A: " << x << '\n';
    }
};

struct B : A
{
    void f(int x) const
    {
        std::cout << "B: " << x << '\n';
    }
    void g(int x)
    {
        std::cout << "B: " << x << '\n';
    }
    virtual int h()
    {
        std::cout << "B: h()\n";
    }
};

int main()
{
    A a;
    B b;
    
    a.f(1);
    a.g(2.0);
    b.f(3);
    b.g(4);
    b.h();
    return 0;
}