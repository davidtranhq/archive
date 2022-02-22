#include <stdio.h>

void arrayinsert(int [], int pos, int val);

void main()
{
	int a[6] = {0, 1, 2, 3, 4, 5};
	int i;
	
	for (i = 0; i < 7; i++)
		printf("%d \n", a[i]);
	
	arrayinsert(a, 3, 8);
	
	for (i = 0; i < 7; i++)
		printf("%d \n", a[i]);
}

void arrayinsert(int a[], int pos, int val)
{
	int i;
	
	for (i = 9; i >= pos; i--)
		if (a[i])
			a[i+1] = a[i];
	a[pos] = val;
}