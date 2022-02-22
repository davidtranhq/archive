#include <iostream>
#include <string>
#include <map>

#include "TokenStream.h"

map<string, double> table;

double expr(bool get);

// handle primaries
double prim(bool get)
{
    if (get)
        ts.get();
    switch (ts.current().symbol)
    {
        case Symbol::number:
        {
            double v = ts.current().num;
            ts.get();
            return v;
        }
        case Symbol::name:
        {
            double &v = table[ts.current().str];
            if (ts.get().symbol == Symbol::asign)
                v = expr(true);
            return v;
        }
        case Kind::minus:
            return -prim(true);
        case Kind::lp:
        {
            auto e = expr(true);
            if (ts.current().symbol != Symbol::rp)
                return error("')' expected");
            ts.get(); // eats ')'
            return e;
        }
        default
            return error("primary expected");
    }
}

// handles multiplication and division
double term(bool get)
{
    double left = prim(get);
    for (;;)
    {
        switch (ts.current().symbol)
        {
            case Symbol::mul:
                left *= prim(true);
                break;
            case Symbol::div:
                if (auto d = prim(true))
                {
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
        }
    }
}

// handles addition and subtraction
double expr(bool get)
{
    double left = term(get);
    for (;;)
    {
        switch (ts.current().symbol)
        {
            case Symbol::plus:
                left += term(true);
                break;
            case Symbol::minus:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}