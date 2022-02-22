#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

void expand(char s1[], char s2[]);
int getchars(char line[], int maxline);

void main()
{	
	char s1[MAXLINE];
	char s2[MAXLINE];
	
	printf("Input: ");
	while (getchars(s1, MAXLINE))
		;
	expand(s1,s2);
	printf("Expanded: %s", s2);
}

int getchars(char s[], int lim)
{
	int c, i, l;
	
	for (i = 0, l = 0; (c = getchar()) != EOF && c != '\n'; i++)
		if (i < lim-1)
			s[l++] = c;
	s[l] = '\0';
	
	return 0;
};

void expand(char s1[], char s2[])
{
	int i,j,k;
	
	for (i = j = 0; s1[i] != '\0'; i++)
	{
		if (s1[i+1] == '-' && isalpha(s1[i]) && isalpha(s1[i+2]) || isdigit(s1[i]) && isdigit(s1[i+2])) //check for 'a-z' or '0-9' format
		{
			for (k = s1[i]; k <= s1[i+2]; ++k)
			{
				s2[j++] = k;
			}
			i += 2;
		}
		else
			s2[j++] = s1[i];
	}
	s2[j] = '\0';
}