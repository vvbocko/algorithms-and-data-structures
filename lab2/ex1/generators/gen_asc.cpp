#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        std::cerr << "Nie podano argumentu\n";
        return 1;
    }

    int n = std::stoi(argv[1]);
    std::cout << n << "\n";

    for(int i=0; i<n; i++)
    {   
        std::cout << i << " " ;
    }

    std::cout << "\n";
    return 0;
}