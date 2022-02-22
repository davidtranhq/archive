#include <iostream>
#include <limits>

int main()
{
    constexpr bool is_char_signed = std::numeric_limits<char>::is_signed;
    if (is_char_signed)
        std::cout << "`char` is signed\n";
    else
        std::cout << "`char` is unsigned\n";
    return 0;
}