#include <iostream>
#include <string>
#include <random>
#include <chrono>

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        std::cerr << "Nie podano argumentu\n";
        return 1;
    }

    int n = std::stoi(argv[1]);
    
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    std::uniform_int_distribution<> randDistribution(0, 2*n-1);
    std::cout << n << "\n";

    for(int i=0; i<n; i++)
    {   
        int randNumber = randDistribution(gen);
        std::cout << randNumber << " " ;
    }

    std::cout << "\n";
    return 0;
}