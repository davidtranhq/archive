#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <cctype>

double error(const std::string &s);
double expr(bool get);

enum class Symbol : char
{
    name, number, end,
    plus='+', minus='-', mul='*', div='/', print=';', assign='=', 
    lp='(', rp=')'
};

struct Token
{
    Symbol sym;
    std::string str;
    double num;
};

class TokenStream
{
    public:
        TokenStream(std::istream &s) : ip{&s}, owns{false} {}
        TokenStream(std::istream *p) : ip{p}, owns{true} {}
        
        ~TokenStream()
        {
            close();
        }
    
        Token get();
        const Token &current()
        {
            return ct;
        }

        void set_input(std::istream &s)
        {
            close();
            ip = &s;
            owns = false;
        }
        void set_input(std::istream *p)
        {
            close();
            ip = p;
            owns = true;
        }
    private:
        void close()
        {
            if (owns)
                delete ip;
        }
        
        std::istream *ip;
        bool owns;
        Token ct {Symbol::end};
};

Token TokenStream::get()
{
    char ch;
    
    // skip whitespace except '\n'
    do {
        if (!ip->get(ch))
            return ct = {Symbol::end};
    } while (ch != '\n' && isspace(ch));
    
    switch (ch)
    {
        case 0:
            return ct = {Symbol::end};
        case ';':
        case '\n':
            return ct = {Symbol::print};
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return ct = {static_cast<Symbol>(ch)};
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            ip->putback(ch);
            *ip >> ct.num;
            ct.sym = Symbol::number;
            return ct;
        default:
            if (isalpha(ch))
            {
                ct.str = ch;
                while (ip->get(ch) && isalnum(ch))
                    ct.str += ch;
                ip->putback(ch);
                return ct = {Symbol::name};
            }
            error("bad token");
            return ct = {Symbol::print};
    }
}


TokenStream ts {std::cin};
std::map<std::string, double> table;
int no_of_errors;

double error(const std::string &s)
{
    no_of_errors++;
    std::cerr << "error: " << s << '\n';
    return 1;
}

double prim(bool get)
{
    if (get)
        ts.get();
    
    switch (ts.current().sym)
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
            if (ts.get().sym == Symbol::assign)
                v = expr(true);
            return v;
        }
        case Symbol::minus:
            return -prim(true);
        case Symbol::lp:
        {
            auto e = expr(true);
            if (ts.current().sym != Symbol::rp)
                return error("')' expected");
            ts.get();
            return e;
        }
        default:
            return error("primary expected");
    }
}

double term(bool get)
{
    double left = prim(get);
    
    for (;;)
    {
        switch (ts.current().sym)
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

double expr(bool get)
{
    double left = term(get);
    
    for (;;)
    {
        switch (ts.current().sym)
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

void calculate()
{
    for (;;)
    {
        ts.get();
        if (ts.current().sym == Symbol::end)
            break;
        if (ts.current().sym == Symbol::print)
            continue;
        std::cout << expr(false) << '\n';
    }
}

int main(int argc, char *argv[])
{
    switch (argc)
    {
        case 1:
            break;
        case 2:
            ts.set_input(new std::istringstream {argv[1]});
            break;
        default:
            error("too many arguments");
            return 1;
    }
    
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;
    
    calculate();
    
    return no_of_errors;
}