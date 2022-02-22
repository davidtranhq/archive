#include <stdio.h>

#define N            6
#define N_FACTORIAL  720L   /* N! */
#define N_OPS        1024L  /* pow(4, N - 1) */

/* Find nth unset bit */
static int nth_unset(unsigned bits, int n)
{
    int i = 0;
    for (; n || ((bits >> i) & 1); i++)
        if (!((bits >> i) & 1))
            n--;
    return i;
}

static int compute(long *v, long permutation, long target)
{
    /* Compute the order for this permutation */
    int order[N];
    unsigned used = 0;
    long factorial = N_FACTORIAL;
    for (int i = 0; i < N; i++) 
	{
        factorial /= N - i;
        order[i] = nth_unset(used, permutation / factorial);
        permutation %= factorial;
        used |= 1u << order[i];
    }

    /* Try all operator combinations */
    for (long i = 0; i < N_OPS; i++)
	{
        char ops[N - 1];
        long total = v[order[0]];
        int abort_loop = 0;
        for (int j = 0; j < N - 1 && !abort_loop; j++) 
		{
            ops[j] = "+-*/"[i >> (2 * j) & 3ul];
            switch (ops[j]) 
			{
                case '+':
                    total += v[order[j + 1]];
                    break;
                case '-':
                    total -= v[order[j + 1]];
                    break;
                case '*':
                    total *= v[order[j + 1]];
                    break;
                case '/':
                    if (total % v[order[j + 1]] == 0)
                        total /= v[order[j + 1]];
                    else
                        abort_loop = 1; /* invalid division */
                    break;
            }
        }

        if (!abort_loop && total == target) 
		{
            /* Print solution and return */
            printf("%ld", v[order[0]]);
            for (int j = 0; j < N - 1; j++)
                printf(" %c %ld", ops[j], v[order[j + 1]]);
            printf(" = %ld\n", target);
            return 1;
        }
    }

    /* No solution found. */
    return 0;
}

int main(void)
{
    long target;
    long numbers[N];
    for (int i = 0; i < N; i++)
        scanf("%ld", numbers + i);
    scanf("%ld", &target);

    /* Visit each permutation */
    for (long i = 0; i < N_FACTORIAL; i++)
        if (compute(numbers, i, target))
            return 0;
    return 1;
}