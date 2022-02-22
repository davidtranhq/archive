#include <stdio.h>

#include "quicksort.h"

int
main()
{
    //int a[] = {13, 8, 11, 9, 8, 9, 2, 7, 3, 9};
    int a[] = {3, 1, 2, 3, 3};
    quicksort(a, 0, 10);
    int i;
    for (i = 0; i < 15; i++)
        printf("%d ", a[i]);
}