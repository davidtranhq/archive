int main()
{
    char c {'c'};
    const char *strings[] = {"Hello", "World!"};
    int j = 42;
    
    char *pc {&c}; // pointer to a char
    int a[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // array of 10 ints 
    int (&ra)[10] {a}; // reference to an array of 10 ints
    const char *(*s)[2] {&strings}; // pointer to an array of character strings
    char **ppc {&pc}; // pointer to a pointer to a char
    const int i = 3.14; // constant int
    const int *pi {&i}; // pointer to constant int
    int *const cpi = &j; // const pointer to int
    
    return 0;
}