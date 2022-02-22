#include <stdio.h>
#include <math.h>

#define MAXHEX 5 //hex length limit
#define HEXDIGIT 48 //diff between ASCII value and hex
#define HEXLETTER 55 //diff between ASCII value and hex
#define CASE 32 //diff between upper/lower case ASCII values
#define HEXBASE 16

int htoi(char s[]);
int strlen(char s[]);
char upper(char c);
int is_hex(char c);

void main()
{
	char s[MAXHEX];
	int i, c;
	
	for (i=0; i<MAXHEX && is_hex(c = getchar()); ++i)
		s[i] = c;
	printf("%.*d", pow(MAXHEX, HEXBASE), htoi(s));		
};

//convert hex string to int
int htoi(char s[MAXHEX])
{
	int i;
	int o = 0;
	
	for (i=strlen(s); i>0; --i)
	{
		if (s[i] >= '0' && s[i] <= '9')
			o = o + (s[i] - HEXDIGIT)*i;
		else if (upper(s[i]) >= 'A' && upper(s[i]) <= 'F')
			o = o + (s[i] - HEXLETTER)*i;
	};
	
	return o;
};

//return string length
int strlen(char s[])
{
	int i = 0;
	
	while (s[i] != '\0')
		++i;
	return i;
}

//return uppercase
char upper(char c)
{
	int u;
	
	if (c >= 'a' || c <= 'z')
		return c + CASE;
	else
		return c;
};

//return true if valid hex char
int is_hex(char c)
{
	if (c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f')
		return 1;
	else
		return 0;
};
