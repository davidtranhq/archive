#include <iostream>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int x {0};
    int y {1};
    
    swap(&x, &y);
    
    std::cout << "x = " << x << ", y = " << y << "\n";
    
    swap(x, y);
    
    std::cout << "x = " << x << ", y = " << y << "\n";
    
    return 0;
}
