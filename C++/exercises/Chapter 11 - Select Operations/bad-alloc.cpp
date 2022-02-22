#include <iostream>
#include <new>
#include <vector>

int main()
{
    unsigned long long allocated = 0; // amount of mem allocated in bytes
    std::vector<char *> v;
    try
    {
        for (;;)
        {
            char *c = new char;
            v.push_back(c); // make sure the new memory is referenced
            *c = 'x';
            allocated++;
        }
    }
    catch (std::bad_alloc)
    {
        std::cerr << "Ran out of memory!\n";
        std::cerr << "Bytes allocated: " << allocated << '\n';
    }
    return 0;
}