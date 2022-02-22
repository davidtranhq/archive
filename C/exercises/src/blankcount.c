#include <stdio.h>

int main() 
{
	int ch;
	int tabs = 0;
	int newlines = 0;
	int blanks = 0;
	
	while ((ch = getchar()) != EOF)
	{
		if (ch == '\t')
			++tabs;
		else if (ch == '\n')
			++newlines;
		else if (ch == ' ')
			++blanks;
	};
	
	printf("Tabs: %d\nNewlines: %d\nBlanks: %d\n", tabs, newlines, blanks);
	
}