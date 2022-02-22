#include <iostream>

template <class T>
array_diff(T *p, T *q)
{
    return q - p;
}

int main()
{
    const char str[] = "Hello World!";
    const char *p = &str[4];
    const char *q = &str[7];
    
    std::cout << "There are " << array_diff(p, q) << " chars between p and q.\n";
    
    const int a[] = {1,2,3,4,5};
    const int *ptr = &a[0];
    const int *qtr = &a[4];
    
    std::cout << "There are " << array_diff(ptr, qtr) << " ints between ptr and qtr.\n";
    
    return 0;
}