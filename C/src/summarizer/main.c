#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hash.h"

#define HASHSIZE 2 /* initial ht size */
#define SENTSIZE 64 /* initial dynamically allocated sentence arr size
                       used by get_sentence() */
typedef enum
{
    ARG_ERR = 1,
    FILE_OPEN_ERR,
    FILE_READ_ERR,
    MEM_ALLOC_ERR,
    NOT_ENUF_SENT_ERR,
} errors_t;

typedef struct sentence
{
    char *s;
    int score;
    struct sentence *next;
} sentence_t;

const char *program_name;

const char* const stop_words[] = {"a", "about", "above", "above", "across", "after", "afterwards", "again", "against", "all", "almost", "alone", "along", "already", "also","although","always","am","among", "amongst", "amoungst", "amount",  "an", "and", "another", "any","anyhow","anyone","anything","anyway", "anywhere", "are", "around", "as",  "at", "back","be","became", "because","become","becomes", "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "bill", "both", "bottom","but", "by", "call", "can", "cannot", "cant", "co", "con", "could", "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", "due", "during", "each", "eg", "eight", "either", "eleven","else", "elsewhere", "empty", "enough", "etc", "even", "ever", "every", "everyone", "everything", "everywhere", "except", "few", "fifteen", "fify", "fill", "find", "fire", "first", "five", "for", "former", "formerly", "forty", "found", "four", "from", "front", "full", "further", "get", "give", "go", "had", "has", "hasnt", "have", "he", "hence", "her", "here", "hereafter", "hereby", "herein", "hereupon", "hers", "herself", "him", "himself", "his", "how", "however", "hundred", "ie", "if", "in", "inc", "indeed", "interest", "into", "is", "it", "its", "itself", "keep", "last", "latter", "latterly", "least", "less", "ltd", "made", "many", "may", "me", "meanwhile", "might", "mill", "mine", "more", "moreover", "most", "mostly", "move", "much", "must", "my", "myself", "name", "namely", "neither", "never", "nevertheless", "next", "nine", "no", "nobody", "none", "noone", "nor", "not", "nothing", "now", "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "our", "ours", "ourselves", "out", "over", "own","part", "per", "perhaps", "please", "put", "rather", "re", "same", "see", "seem", "seemed", "seeming", "seems", "serious", "several", "she", "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some", "somehow", "someone", "something", "sometime", "sometimes", "somewhere", "still", "such", "system", "take", "ten", "than", "that", "the", "their", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "therefore", "therein", "thereupon", "these", "they", "thickv", "thin", "third", "this", "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", "too", "top", "toward", "towards", "twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us", "very", "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", "while", "whither", "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within", "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves"}; /* english words that add no value (stop words) */

static void handle_error(errors_t e);
/*
    error: prints error message based on code e and exits
*/

size_t file_length(FILE *fp);
/*
    file_length: returns length of file in bytes
*/

char *copy_file(FILE *fp);
/*
    copy_file: allocates memory and copies file contents into heap, 
    returns char pointer to contents
*/

hashtable_t *count_words(char *s);
/*
    count_words: counts words in s, stores result in a hashtable and returns
    a pointer to it
*/

void index_word(char *w, hashtable_t **ht);
/*
    index_word: inserts w as a key into the ht if it is unique and not a
    stop word, otherwise increments it's value. double pointer to ht used
    to modify the pointer in case the table is resized.
*/

int is_stop_word(char *w);
/*
    is_stop_word: returns 1 if found in list of stop_words, else returns 0
*/

void lower_str(char *s);
/*
    lower_str: lowers the case of all letters in a string.
*/

size_t split_to_sentences(char *t, sentence_t **sentence);
/*
    split_to_sentences: splits t into a (malloc()) linked list of sentences.
    points sentence to the head of the list. returns the number of sentences
    found.
*/

sentence_t *new_node(char *s);
/*
    new_node: creates a new sentence_t with a string value of s 
    to be used in the linked list created  by split_to_sentences()
*/

char *get_sentence(char *s);
/*
    get_sentence: gets the next sentence in string s. pass NULL to keep
    reading from same string. returns the sentence in a string allocated
    with malloc()
*/

sentence_t *alloc_sentence(void);
/*
    alloc_sentence: allocates a sentence_t and returns a pointer to it.
    returns NULL if allloc failed.
*/

char is_punc(char c);
/*
    is_punc: checks if c is a sentence terminating punctuation. returns c if
    true, 0 if false
*/

void score_sentences(sentence_t *st, hashtable_t *ht);
/*
    score_sentences: loops through the linked list of sentence_t's pointed
    to by the head st. calls score_sentence() on each to score the sentence.
*/

void score_sentence(sentence_t *st, hashtable_t *ht);
/*
    score_sentence: scores a sentence based on the importance of it's
    words using the data from the hashtable ht.
*/

int compare(const void *a, const void *b);
/*
    compare: returns >0 if a > b, <0 if a < b. comparator function for
    qsort()
*/

static void 
handle_error(errors_t e)
{
    fprintf(stderr, "%s: error %i:\n", program_name, e);
    switch (e)
    {
        case ARG_ERR:
            fprintf(stderr, "usage: %s <filename> <#> [output]", 
                    program_name);
            break;
        case FILE_OPEN_ERR:
            fputs("error opening file", stderr);
            break;
        case FILE_READ_ERR:
            fputs("error reading file", stderr);
            break;
        case MEM_ALLOC_ERR:
            fputs("error allocating memory (probably not enough memory)", stderr);
            break;
        case NOT_ENUF_SENT_ERR:
            fprintf(stderr, "not enough sentences in input text.");
    }
    exit(e);
}

size_t 
file_length(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t bufsize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return bufsize;
}

char *
copy_file(FILE *fp)
{
    size_t len = file_length(fp);
    char *buf;
    /* try to alloc enough memory for file */
    if ((buf = malloc(len)) == NULL)
        handle_error(MEM_ALLOC_ERR);
    /* copy file into buffer */
    size_t chread = fread(buf, 1, len, fp);
    if (ferror(fp))
        handle_error(FILE_READ_ERR);
    buf[chread] = '\0';
    return buf;
}

hashtable_t *
count_words(char *s)
{
     /* copy text to be manipulated by strtok() */
    char *scpy;
    if ((scpy = strdup(s)) == NULL)
        handle_error(MEM_ALLOC_ERR);
    /* attempt to create hash table */
    hashtable_t *ht;
    if ((ht = ht_create(HASHSIZE, INTEGER)) == NULL)
        handle_error(MEM_ALLOC_ERR);
    /* loop through and index words */
    const char *delim = " \t\n,.!?'\"()[]:;";
    char *w = strtok(scpy, delim);
    while (w != NULL)
    {
        lower_str(w);
        index_word(w, &ht);
        w = strtok(NULL, delim);
    }
    free(scpy);
    return ht;
}

void 
index_word(char *w, hashtable_t **ht)
{
    int *count, init_val = 1;
    if ((count = ht_get(*ht, w)) == NULL)
    {
        /* not found, insert */
        if (ht_insert(&(*ht), w, &init_val) < 0)
            handle_error(MEM_ALLOC_ERR);
    }
    else
        /* found, increment word's count */
        (*count)++;
}

int 
is_stop_word(char *w)
{
    /* get length of stop_words array */
    int n = sizeof(stop_words)/sizeof(stop_words[0]);
    /* binary search */
    int lo = 0, hi = n-1, mid;
    while (lo <= hi)
    {
        mid = (lo + hi)/2;
        if (strcmp(w, stop_words[mid]) == 0)
            return 1; /* found*/
        else if (strcmp(w, stop_words[mid]) > 0)
            lo = mid+1;
        else
            hi = mid-1;
        
    }
    /* not found */
    return 0;
}

void 
lower_str(char *s)
{
    for ( ; *s; s++) *s = tolower(*s);
}

size_t 
split_to_sentences(char *t, sentence_t **head)
{
    sentence_t *sentence, *tail;
    char *s;
    size_t count = 0;
    s = get_sentence(t);
    sentence = new_node(s);
    /* remember the tail of the linked list */
    *head = sentence;
    tail = sentence;
    /* continue reading the sentences until the end is reached */
    while ((s = get_sentence(NULL)) != NULL)
    {
        count++;
        sentence = new_node(s);
        tail->next = sentence;
        tail = sentence;
    }
    return count;
}

sentence_t *
new_node(char *s)
{
    sentence_t *sentence;
    if ((sentence = alloc_sentence()) == NULL)
        handle_error(MEM_ALLOC_ERR);
    sentence->s = s;
    sentence->score = 0;
    sentence->next = NULL;
    return sentence;
}

char *
get_sentence(char *t)
{
    static char *text = NULL; /* keep our place between successive calls */
    static char *bufp = NULL; /* used to scan through the string */
    if (text == NULL)
    {
        if (t == NULL)
        {
            /* string has never been passed, error */
            return NULL;
        }
        else
        {
            /* string is passed for first time */
            text = t;
            bufp = t;
        }
    }
    if (t != text)
    {
        if (t == NULL)
        {
            /* used old string */
        }
        else
        {
            /* a new string has been passed */
            text = t;
            bufp = t;
        }
    }
    /* step through until a punctuation mark followed by a space or \0 is found */
    for ( ; !is_punc(*bufp) || !isspace( *(bufp+1) ); ++bufp)
        if (*(bufp+1) == '\0')
            break;
    /* calc length of sentence from starting point to punc mark, +1 includes
       punctuation */
    size_t len = bufp+1 - text;
    /* alloc sentence, +1 for null terminator */
    char *sent;
    if ((sent = malloc(len+1)) == NULL)
        handle_error(MEM_ALLOC_ERR);
    /* copy substring (sentence) into sent */
    strncpy(sent, text, len);
    *(sent+len) = '\0';
    /* if bufp+1 is '\0' we've reached the end of string, reset 'trackers' */
    if (*(bufp+1) == '\0')
    {
        text = NULL;
        bufp = NULL;
        return sent;
    }
    /* update our position in the string for the next call, +2 on both
       'trackers' to skip over the punc and the space */
    text = bufp+2;
    bufp += 2;
    return sent;
}

char 
is_punc(char c)
{
    switch (c)
    {
        case '.':
        case '!':
        case '?':
            return c;
            break;
        default:
            return 0;
    }
}

sentence_t *
alloc_sentence(void)
{
    return malloc(sizeof(sentence_t));
}

void 
score_sentences(sentence_t *head, hashtable_t *ht)
{
    sentence_t *tmp;
    for (tmp = head; tmp != NULL; tmp = tmp->next)
    {
        score_sentence(tmp, ht);
    }
}

void 
score_sentence(sentence_t *st, hashtable_t *ht)
{
    /* copy to be manipulated by strtok() */
    char *scpy;
    if ((scpy = strdup(st->s)) == NULL)
        handle_error(MEM_ALLOC_ERR);
    const char *delim = " \t\n,.!?'\"()[]:;";
    char *w = strtok(scpy, delim);
    int *count;
    while (w != NULL)
    {
        lower_str(w);
        if (!is_stop_word(w))
        {
            count = ht_get(ht, w);
            st->score += *count;
        }
        w = strtok(NULL, delim);   
    }
}

int
compare(const void *a, const void *b)
{
    return ( *(int *)a - *(int *)b );
}

void 
sort_scores(sentence_t *head, int a[])
{
    sentence_t *tmp;
    size_t i;
    /* fill the array with sentence scores */
    for (i = 0, tmp = head; tmp != NULL; i++, tmp = tmp->next)
        a[i] = tmp->score;
    qsort(a, i, sizeof(int), compare);
}

int 
main(int argc, char *argv[])
{
    program_name = argv[0];
    /* correct usage? */
    if (argc < 3)
        handle_error(ARG_ERR);
    const int summary_len = atoi(argv[2]);
    if (summary_len < 1)
        handle_error(ARG_ERR);
    /* open output file if specified */
    FILE *fout;
    if (argc > 3)
    {
        if ((fout = fopen(argv[3], "w")) == NULL)
            handle_error(FILE_OPEN_ERR);
    }
    else
    {
        fout = stdout;
    }
    /* attempt to open file */
    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == NULL)
        handle_error(FILE_OPEN_ERR);
    /* read file */
    char *text;
    text = copy_file(fp);
    /* count word occurences */
    hashtable_t *words;
    words = count_words(text);
    /* split into sentences */
    sentence_t *sentences;
    size_t sentence_count;
    sentence_count = split_to_sentences(text, &sentences);
    /* enough sentences? */
    if (sentence_count < summary_len)
        handle_error(NOT_ENUF_SENT_ERR);
    /* score sentences based on word importance */
    score_sentences(sentences, words);
    /* sort sentence scores */
    int scores[sentence_count];
    sort_scores(sentences, scores);
    /* output the sentences based on their weight */
    sentence_t *st;
    size_t printed = 0;
    for (st = sentences; 
         st->next != NULL && printed < summary_len; 
         st = st->next)
        if (st->score >= scores[sentence_count - summary_len])
        {
            fprintf(fout, "%s ", st->s);
            printed++;
        }
    return 0;
}