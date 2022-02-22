#include <iostream>

class Complex
{
    public:
        constexpr complex(double r = 0; double i = 0);
        
        constexpr double real() const;
        constexpr double imag() const;

        void real(double r);
        void imag(double i);
        
        complex &operator+=
        
    private:
        double re, im;
}

int main()
{
    return 0;
}