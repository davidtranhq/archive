#include <stdio.h>

void main()
{
	int i;
	char p[] = {0, -1, 1};
	
	printf("Enter a number: ");
	scanf("%d",&i);
	while (i != 1)
	{
		printf("%d, %d\n", i, p[i%3]);
		i = i%3 ? i+p[i%3] : i/3;
	}
	printf("%d", i);
};
