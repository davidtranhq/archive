#include <string>
#include <iostream>

std::string *cat(const char *s1, const char *s2)
{
    std::string *res = new std::string {};
    for (; *s1; s1++)
        *res += *s1;
    for (; *s2; s2++)
        *res += *s2;
    return res;
}

int main()
{
    const char *str1 = "Hello";
    const char *str2 = "World!";
    std::cout << *cat(str1, str2) << '\n';
    return 0;
}