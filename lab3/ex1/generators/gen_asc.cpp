#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    if (argc < 3) 
    {
        std::cerr << "Nie podano argumentów\n";
        return 1;
    }

    int n = std::stoi(argv[1]);
    int k = std::stoi(argv[2]);
    
    std::cout << n << " " << k << "\n";

    for(int i=0; i<n; i++)
    {   
        std::cout << i << " " ;
    }

    std::cout << "\n";
    return 0;
}