#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

/* compare: compare files, printing first differing line */
int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    int i;
    char *prog = argv[0];
    
    /*require 2 files to comp*/
    if (argc != 3)
    {
        fprintf(stderr, "Incorrect usage: got %d arguments, expected 3", argc);
        exit(1);
    }
    /*attempt to open files*/
    if (!( (fp1 = fopen(argv[1], "r")) && (fp2 = fopen(argv[2], "r")) ))
    {
        fprintf(stderr, "%s: can't open %s\n", prog, argv[1] ? argv[1] : argv[2]);
        exit(2);
    }
    /*read line from each file*/
    for (i = 1; fgets(line1, MAXLINE, fp1) && fgets(line2, MAXLINE, fp2); i++)
    {
        if (strcmp(line1, line2))
        {
            /* print line # and line that differed */
            fprintf(stdout, "Difference at line %d:\n%s: %s\n%s: %s\n", 
                    i, argv[1], line1, argv[2], line2);
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
    
    return 0;
}