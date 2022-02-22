#include <string>
#include <iostream>

enum class Symbol : char
{
    name, number, end,
    plus='+', minus='-', mul='*', div='/', lp='(', rp=')', print=';', assign='='
};

struct Token
{
    Symbol sym;
    std::string str_val;
    double num_val;
};

