#include <limits.h>
#include <stdio.h>

#define MAXINP 255;
unsigned int bincat(unsigned int, char);
/*
    bincat: appends CHAR_BIT bits to an unsigned int
*/

unsigned int bincat(unsigned int a, char b)
{
    return (unsigned int) (a << CHAR_BIT) | b;
}

void encode(char *in, char *out)
{
    char *p;
    size_t i;
    unsigned int val = 0;
    for (p = in, i = 1; *p; ++p, ++i)
    {
        /* concatenate every 4 chars into an int */
        val = bincat(val, *p);
        if (i % 4 == 0)
        {
            /* encode value into 4 ASCII chars */
            int j;
            for (j = 0; j < 4; j++)
                *(out++) = val % 85 + 33;
        }
    }
}

int main(int argc, char *argv[])
{
    char op = 0, s[MAXINP];
    scanf("%c %s", &c, s);
    if (c == 'e')
        en
    return 0;
}