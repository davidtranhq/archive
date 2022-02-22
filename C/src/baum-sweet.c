/*
https://www.reddit.com/r/dailyprogrammer/comments/7j33iv/20171211_challenge_344_easy_baumsweet_sequence/?ref=share&ref_source=link

In mathematics, the Baum–Sweet sequence is an infinite automatic sequence of 0s and 1s defined by the rule:

    b_n = 1 if the binary representation of n contains no block of consecutive 0s of odd length;
    b_n = 0 otherwise;

for n >= 0.

*/

#include <stdio.h>

int baum_sweet(unsigned int n)
{
    int z; /* # of 0s in current block */
    for (z = 0; n; n >>= 1)
    {
        if (n & 1u)
        {
            if (z & 1u)
                return 0;
        }
        else
        {
            z++;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    puts("Prints the Baum-Sweet sequence from 0 to n where n>=0.");
    fputs("n = ", stdout);
    unsigned int n;
    scanf("%u", &n);
    for (unsigned int i = 0; i < n+1; i++)
        printf("%d, ", baum_sweet(i));
    return 0;
}