#include <stdio.h>

int main()
{
	int ch;
	int isSpace = 0;
	
	while ((ch = getchar()) != EOF)
	{
		if (ch == ' ' || ch == '\t' || ch == '\n')
			if (!isSpace)
			{
				putchar('\n');
				isSpace = 1;
			}
		else
			putchar(ch);
	};
	
	return 0;
}