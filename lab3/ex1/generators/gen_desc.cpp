#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    if (argc < 3) 
    {
        std::cerr << "Nie podano argumentu\n";
        return 1;
    }

    int n = std::stoi(argv[1]);
    int k = std::stoi(argv[2]);
    
    std::cout << n << " " << k << "\n";

    for(int i=n-1; i>=0; i--)
    {   
        std::cout << i << " " ;
    }

    std::cout << "\n";
    return 0;
}