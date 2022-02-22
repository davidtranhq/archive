#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

void main()
{
	char s[] = "This is a tab\tand this is a newline\n";
	char t[20];
	char u[20];
	escape(s,t);
	printf("Escaped: %s", t);
	unescape(t, u);
	printf("\nUnescaped: %s", u);
};

//copies s to t, replacing all formatting with formatting code
void escape(char s[], char t[])
{
	int i, j;
	
	for (i = j = 0; s[i] != '\0'; i++)
	{
		switch (s[i])
		{
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;
			default:
				t[j++] = s[i];
				break;
		}
	}
	t[j] = '\0';
}

//copies s to t, replacing all formatting codes with formatting
void unescape(char s[], char t[])
{
	int i, j;
	
	for (i = j = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '\\')
			switch (s[++i])
			{
				case 'n':
					t[j++] = '\n';
					break;
				case 't':
					t[j++] = '\t';
					break;
				default:
					t[j++] = '\\';
					t[j] = s[i];
					break;
			}
		else
			t[j++] = s[i];
		
	}
	t[j] = '\0';
}