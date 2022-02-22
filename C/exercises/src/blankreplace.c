#include <stdio.h>

int main()
{
	int ch;
	int isExtraSpace = 0;
	
	while ((ch = getchar()) != EOF)
	{
		if (ch == ' ')
		{
			if (!isExtraSpace)
			{
				isExtraSpace = 1;
				putchar(ch);
			};
		}
		else
		{
			isExtraSpace = 0;
			putchar(ch);
		};
	};
	
	return 0;
}
				