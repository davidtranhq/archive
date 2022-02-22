#include <stdio.h>
#define MAXWORD 11 //maximum word length

void main()
{
	int c, i;
	int word_lengths[MAXWORD];
	int len = 0; //current word length
	int is_word = 0;
	
	for (i=1; i<MAXWORD; ++i)
		word_lengths[i] = 0;
	
	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
		{
			if (is_word)
			{
				++word_lengths[len];
				len = 0;
			};
			is_word = 0;
		}
		else
		{
			is_word = 1;
			++len;
		};
	};
	
	for (i=1; i<MAXWORD; ++i)
	{
		printf("%5d %5d - ", i, word_lengths[i]);
		while (word_lengths[i] > 0)
		{
			putchar('*');
			--word_lengths[i];
		};
		putchar('\n');
	};
};