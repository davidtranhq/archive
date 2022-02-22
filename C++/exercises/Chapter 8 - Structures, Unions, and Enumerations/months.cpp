#include <iostream>
#include <iomanip>

struct Month
{
    const char *name;
    const int days;
};

int main()
{
    // implemented using arrays 
    const char *months[] = {"Jan", "Feb", "Mar",  "Apr", "May", "Jun", "Jul", 
    "Aug", "Sep", "Oct", "Nov", "Dec"};
    const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    for (const char *m : months)
        std::cout << std::setw(4) << m;
    std::cout << '\n';
    for (const int d: days)
        std::cout << std::setw(4) << d;
    std::cout << '\n';
    // implemented using structs
    
    Month calendar[] = 
    { 
        {"Jan", 31}, {"Feb", 28}, {"Mar", 31}, {"Apr", 30},
        {"May", 31}, {"Jun", 30}, {"Jul", 31}, {"Aug", 31},
        {"Sep", 30}, {"Oct", 31}, {"Nov", 30}, {"Dec", 31}
    };
    
    for (Month m : calendar)
        std::cout << m.name << ' ' << m.days << '\n';
        
    return 0;
}