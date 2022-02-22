#include <stdio.h>
#include <stdlib.h>

int random(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}

int quickselect(int *a, int l, int k) //pointer, length, k-th element
{
	int piv = *(a+random(0, l-1));
	
	int *less = malloc(sizeof(int)*l), *great = malloc(sizeof(int)*l); //allocate to the max possible size
	int l_len = 0, g_len = 0;
	
	for (int i = 0; i < l; i++)
		if (*(a+i) < piv) 
			*(less+l_len++) = a[i]; //set "array indice" (dereferneced pointer) and increment array len
		else if (*(a+i) > piv)
			*(great+g_len++) = a[i];
	
	less = realloc(less, sizeof(int)*l_len); //re-allocate appropiate to the proper size
	great = realloc(great, sizeof(int)*g_len);
	
	if (k <= l_len)
		return quickselect(less, l_len, k);
	else if (k > l - g_len)
		return quickselect(great, g_len, k - (l - g_len));
	else
		return piv;
}

int main()
{
	int a[] = {5,2,6,3,7,1,0};
	printf("%d", quickselect(a, sizeof(a)/sizeof(*a), 5));
	return 0;
}