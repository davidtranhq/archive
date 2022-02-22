#include <iostream>
#include <string>

int main()
{
    std::string months[] {"January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December"};
    
    for (const std::string month : months)
        std::cout << month << "\n";
    return 0;
}