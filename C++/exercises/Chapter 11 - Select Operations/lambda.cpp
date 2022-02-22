#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void print_modulo(const std::vector<int> &v, std::ostream &os, int m)
    // output v[i] to os if v[i] is divisible by m
{
    std::for_each(std::begin(v), std::end(v),
        [&os, m](int x) { if (x%m == 0) os << x << '\n'; }
    );
}

int main()
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 100);
    
    print_modulo(v, std::cout, 3);
    return 0;
}

/* equivalent function object */

class Modulo_print 
{
    private:
        ostream& os;
        int m;
    public:
        Modulo_print(ostream& s, int mm) :os(s), m(mm) {}
        void operator()(int x) const
            { if (x%m==0) os << x << '\n'; }
};

/* defining a lambda */

void f(sttd::string &s1, std::string &s2)
{
    /* lambda declared with variable of type std::function<R(AL)>, where R is the lambda's
        return type and AL is its argument list of types */
    std::function<void(char *b, char *e)> rev =
        [&](char *b, char *e) { if (1 < e-b) { swap(*b, *--e); rev(++b, e); } };
}