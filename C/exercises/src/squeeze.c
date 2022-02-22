#include <stdio.h>

void squeeze(char s1[], char s2[]);

void main()
{
	char s1[] = "abcdef";
    char s2[] = "bdf";
	
    squeeze(s1, s2);
    printf("%s\n", s1);

};

void squeeze(char s1[], char s2[])
{
	int i, j, k;
	int is_in_str;
	
	for (i = j = 0; s1[i] != '\0'; ++i) {
		is_in_str = 0;
		for (k = 0; s2[k] != '\0'; ++k)
			if (s1[i] == s2[k])
				is_in_str = 1;
		if (!is_in_str)
			s1[j++] = s1[i];
	};
	s1[j] = '\0';
};