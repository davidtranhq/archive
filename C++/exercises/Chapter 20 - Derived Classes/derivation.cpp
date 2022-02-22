#include <iostream>

class Base
{
    public:
        virtual void iam() { std::cout << "Base\n"; }
};

class Child : public Base
{
    public:
        void iam() override { std::cout << "Child\n"; }
};

class Kid : public Base
{
    public:
        void iam() override { std::cout << "Kid\n"; }
};

int main()
{
    Child c;
    Kid k;
    
    c.iam();
    k.iam();
    
    Base *pc = &c;
    Base *pk = &k;
    
    pc->iam();
    pk->iam();
    
    return 0;
}