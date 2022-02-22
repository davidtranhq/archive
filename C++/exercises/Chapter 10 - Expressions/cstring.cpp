#include <iostream>

size_t strlen(const char *s)
{
    size_t len;
    for (len = 0; *s++; len++);
    return len;
}

char *strcpy(char *s1, const char *s2)
{
    while (*s1++ = *s2++)
        ;
    return s1;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1++ == *s2++))
        ;
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int main()
{
    const char *s = "Hello World!";
    char *str;
    
    std::cout << strlen("Hello") << '\n';
    strcpy(str, s);
    std::cout << str << '\n';
    std::cout << strcmp("ABC", "DEF");
    return 0;
}