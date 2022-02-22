#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0; //next free position

struct wordtree
{
	char *word;
	int count;
	struct wordtree *left;
	struct wordtree *right;
};

char getword(char *, int);
int getch();
void ungetch(char);
struct wordtree *addtree(struct wordtree *, char *);
struct wordtree *makenode(void);
void printtree(struct wordtree *);
void strtolower(char *);

void main()
{
	char word[MAXWORD];
	struct wordtree *root;
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	printtree(root);
}

struct wordtree *addtree(struct wordtree *t, char *word)
{
	int cond;
	
	strtolower(word);
	if (t == NULL)
	{
		t = makenode();
		t->word = strdup(word);
		t->count = 1;
		t->left = NULL;
		t->right = NULL;
	}
	else if ((cond = strcmp(t->word, word)) > 0)
		t->left = addtree(t->left, word);
	else if (cond == 0)
		(t->count)++;
	else
		t->right = addtree(t->right, word);
	return t;
}

struct wordtree *makenode()
{
	return (struct wordtree *) malloc(sizeof(struct wordtree)); 
}

void printtree(struct wordtree *t)
{
	if (t != NULL)
	{
		printtree(t->left);
		printf("%4d %s\n", t->count, t->word);
		printtree(t->right);
	};
}


char getword(char *word, int lim)
{
	int c;
	char *w = word;
	
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c))
	{
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '\'')
		{
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

int getch()
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(char c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void strtolower(char *p)
{
	for (; *p; p++) *p = tolower(*p);
}