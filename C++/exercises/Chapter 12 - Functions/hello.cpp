#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> getNames(int argc, char *argv[])
{
    std::vector<std::string> names;
    names.reserve(argc);
    for (int i {1}; i < argc; i++)
        names.push_back(argv[i]);
    return names;
}

void sayHello(std::vector<std::string> names)
{
    std::string greet {"Hello"};
    for (auto n : names)
        greet += ' ' + n + ',';
    greet.back() = '!';
    std::cout << greet << std::endl;
}

// takes any number of names as a command-line argument
// and says hello to each
int main(int argc, char *argv[])
{
    std::vector<std::string> names {getNames(argc, argv)};
    sayHello(names);
    return 0;
}