#include <stdio.h>

#include "quicksort.h"

static int partition(int a[], int left, int right, int pivot);
static void swap(int *a, int *b);

static void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

static int partition(int a[], int left, int right, int pivot)
{
    int i, j;
    int tmp;
    for (;;)
    {
        /* while left pointer is less than pivot move right */
        for (i = left; (a[i] < pivot) && (i <= right); i++);
        /* while right pointer is greater than pivot move left */
        for (j = right-1; (a[j] > pivot) && (j >= left); j--);
        if (i >= j)
        {
            /* pointers have met, meeting point is position of the pivot */
            swap(a+i, a+right);
            break;
        }
        swap(a+i, a+j);
    }
    return i;
}

void quicksort(int a[], int left, int right)
{
    if (left < right)
    {
        int pivot = a[right];
        int part;
        part = partition(a, left, right, pivot);
        quicksort(a, left, part-1);
        quicksort(a, part+1, right);
    }
}
