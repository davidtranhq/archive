#include <iostream>
#include <string>

int main()
{
    std::string s {"4 5 9 17 12 "};
    std::string out {};
    for (char &c : s)
    {
        if (c == ' ')
        {
            out += "\n";
            std::cout << out;
            out = "";
        }
        else
        {
            out += c;
        }
    }
    return 0;
}