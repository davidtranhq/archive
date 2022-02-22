// cat.cpp: concatenates files
#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " [file1] [file2]..." << std::endl;
        exit(1);
    }
    std::vector<char *> files(argv+1, argv+argc); // vector containing file names
    for (auto n : files)
    {
        std::ifstream f(n);
        
        if (!f.is_open())
        {
            std::cerr << "Couldn't open file: " << n << std::endl;
            exit(2);
        }
        std::cout << f.rdbuf();
        f.close();
    }
}