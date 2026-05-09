#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <cmath>
#include <iomanip>

double log_base(double base, double x)
{
    return std::log(x) / std::log(base);
}

double func(int func_num, double x)
{
    if(func_num == 1)
    {
        return std::pow(log_base(2,x+1), 3);
    }
    else return std::sqrt(x) + log_base(2, x+1);
}


int main(int argc, char* argv[]) 
{
    std::cout << std::fixed << std::setprecision(15);
    
    if (argc < 4) 
    {
        std::cerr << "Nie podano argumentu\n";
        return 1;
    }

    int n = std::stoi(argv[1]);
    double q = std::stod(argv[2]);
    int func_num = std::stoi(argv[3]);

    if (func_num != 1 && func_num != 2) 
    {
        std::cerr << "numer funkcji 1 lub 2\n";
        return 1;
    }
    
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    std::cout << n << " " << q << " " << func_num << "\n";

    double last_val = -1.0;
    double delta = (func_num == 1) ? 10.0 : 50.0;
    
    for(int i=0; i<n; i++) {   
        double lower_bound = std::max(last_val, func(func_num, i));
        double upper_bound = func(func_num, i) + delta;
        std::uniform_real_distribution<double> randDistribution(lower_bound, upper_bound);
        double randNumber = randDistribution(gen);
        last_val = randNumber;
        std::cout << randNumber << " " ;
    }

    std::cout << "\n";
    return 0;
}