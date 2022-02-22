#include <iostream>
#include <cstdarg>
#include <string>

int error(std::string fmt, ...)
{
    using std::string;
    va_list ap;
    va_start(ap, fmt);
    for (char c : fmt)
    {
        switch (c)
        {
            case '%s':
            {
                std::string s = va_arg(ap);
                std::cerr << s;
            }
            case '%d':
            {
                int d = va_arg(d);
                
    }
}

int main()
{
    return 0;
}