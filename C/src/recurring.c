#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#define MAXINP 64

void lower_str(char *s)
{
    for ( ; *s; ++s)
        tolower(*s);
}

int main(void)
{
    char inp[MAXINP];
    if (fgets(inp, MAXINP, stdin) == NULL)
        fputs("error reading string, may be too long", stderr);
    lower_str(inp);
    uint32_t alpha = 0, tmp; /* bitfield to contain letter occurences */
    char c = 0;
    size_t i;
    for (i = 0; inp[i]; i++)
    {
        uint32_t mask = 2^(inp[i] - 96); /* mask based on the exponent of the
        letter's ASCII value. 97 is the ASCII value of 'a' so we will start at
        1. */
        tmp = alpha;
        alpha |= mask;
        if (tmp == mask) /* if the masked fields match, we've already masked 
        that letter therefore it has occured. */
        {
            c = *inp;
            break;
        }
    }
    if (c == 0)
        puts("There are no recurring characters.");
    else
        printf("The first recurring character is: %c", c);
    return 0;
}