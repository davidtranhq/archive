#include <string>

std::string operator""SS(const char *p);

int main()
{
    std::string s12 = "one two"SS;
    return 0;
}