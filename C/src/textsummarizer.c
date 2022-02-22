#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXTEXT 1000
#define MAXWORD 30
#define MAXSTOP 200

#define SUMLENGTH 1 //in sentences

typedef struct tnode Wnode;

typedef struct tnode
{
	char *word;
	int score;
	struct tnode *left;
	struct tnode *right;
} Wnode; //binary search tree nodes

char getword(char inp[], char *out, int lim);
Wnode *addtree(Wnode *, char *w);
Wnode *makenode(void);
void printtree(Wnode *);
int isstopword(char *);
int getwordscore(Wnode *root, char *);
int quickselect(int a[], int l, int k);
int random(int low, int high);
void strtolower(char *s1, char *s2);

int main()
{
	char text[MAXTEXT];
	char word[MAXWORD];
	char stopwords[MAXSTOP][MAXWORD];
	char *sentences[MAXTEXT];
	int sentence_scores[MAXTEXT];
	int sentence_index_rank[MAXTEXT];
	char sentence[MAXTEXT];
	Wnode *root;
	int i, j, c;
	FILE *fp;
	
	fp = fopen("stopwords.txt", "r");
	
	//TODO: check for word seperator, assumes sep is space
	for (i = j = 0; i < MAXSTOP && (c = fgetc(fp)) != EOF; j++)
		if (isspace(c))
		{
			i++;
			j = 0;
		}
		else
			stopwords[i][j] = c;
	
	for (i = 0; i < MAXTEXT && (c = getchar()) != EOF; i++)
		text[i] = c;
	text[++i] = '\0';
	
	root = NULL;
	while (getword(text, word, MAXWORD) != '\0')
		if (isalpha(word[0]) && !isstopword(word))
			root = addtree(root, word);
	printtree(root);
	
	sentence[0] = '\0';
	i = 0;
	int sentence_count = 0;
	while (getword(text, word, MAXTEXT) != '\0')
	{
		if (isalpha(word[0]) && !isstopword(word))
		{
			strcat(strcat(sentence, " "), word);
			sentence_scores[i] += getwordscore(root, word);
		}
		else if (word[0] == '.' || word[0] == '\0')
			sentences[i++] = strdup(strcat(sentence, "."));
		
	};
	
	if (i <= SUMLENGTH)
	{
		printf("Not enough sentences to summarize.\n");
		return EXIT_FAILURE;
	}
	
	int min_rank = quickselect(sentence_scores, i, i-SUMLENGTH);
	
	for (i = 0; i <= MAXTEXT && sentences[i]; i++)
		if (sentence_scores[i] >= min_rank)
			printf("%s", sentences[i]);
		
	return EXIT_SUCCESS;
}

char getword(char s[], char *w, int lim)
{
	static int bufp = 0;
	char c;
	char *word = w;
	while (isspace(c = s[bufp++]));
	
	if (c != '\0')
		*w++ = c;
	else if (!isalpha(c))
	{
		if (c == '\0')
			bufp = 0; //return to beginning of buffer when finished
		*w = '\0';
		return c;
	};
	
	for (; --lim > 0; bufp++)
		if (isalpha(c = s[bufp]) || c == '\'')
			*w++ = s[bufp];
		else
			break;
	*w = '\0';
	return word[0];
}

Wnode *addtree(Wnode *n, char *w)
{
	int cond;
	
	if (n == NULL)
	{
		n = makenode();
		n->word = strdup(w);
		n->score = 1;
		n->left = NULL;
		n->right = NULL;
	}
	else if ((cond = strcmp(n->word, w)) > 0)
		n->left = addtree(n->left, w);
	else if (cond == 0)
		(n->score)++;
	else
		n->right = addtree(n->right, w);
	return n;
}

Wnode *makenode(void)
{
	return (Wnode *) malloc(sizeof(Wnode));
}

void printtree(Wnode *n)
{
	if (n != NULL)
	{
		printtree(n->left);
		printf("%4d %s\n", n->score, n->word);
		printtree(n->right);
	};
}

int getwordscore(Wnode *t, char *s)
{
	int cond;

	while ((cond = strcmp(t->word, s)) != 0)
		if (cond > 0)
			if (t->left == NULL)
				return 0;
			else
				t = t->left;
		else
			if (t->right == NULL)
				return 0;
			else
				t = t->right;
	return t->score;
}

int quickselect(int a[], int l, int k)
{
	int piv = a[random(0, l)];
	
	int *less = malloc(sizeof(int)*l), *great = malloc(sizeof(int)*l);
	int l_len = 0, g_len = 0;
	
	for (int i = 0; i < l; i++)
		if (a[i] < piv)
			*(less+l_len++) = a[i];
		else if (a[i] > piv)
			*(great+g_len++) = a[i];
	
	less = realloc(less, sizeof(int)*l_len);
	great = realloc(great, sizeof(int)*g_len);
	
	if (k <= l_len)
		return quickselect(less, l_len, k);
	else if (k > l - g_len)
		return quickselect(great, g_len, k - (l - g_len));
	else
		return piv;
}

int random(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}

int isstopword(char *w)
{
	for (int i = 0; i < MAXSTOP && stopwords[i]; i++)
		if (strcmp(*w, stopwords[i]) == 0)
			return 1;
		else
			return 0;
}