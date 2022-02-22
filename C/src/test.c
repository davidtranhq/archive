#include <stdio.h>

int main(void)
{
    int x = 9;
    for (; x < 10; ++x)
        ;
    printf("%d", x);
}