/*  
    Exercise 1-1:
    Run the "hello, world" program on your system. Experiment with leaving out
    parts of the program, to see what error messages you get.
*/

/*
    leave the following out and you'll get:
    exercise1-1.c:11:5: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     printf("hello, world\n");
     ^~~~~~
    exercise1-1.c:11:5: warning: incompatible implicit declaration of built-in function 'printf'
    exercise1-1.c:11:5: note: include '<stdio.h>' or provide a declaration of 'printf'
*/

#include <stdio.h>

int main()
{
    printf("hello, world\n");
    return 0;
}