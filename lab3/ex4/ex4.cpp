#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <limits>
#include <algorithm>
#include <iomanip>

long long compareCount = 0;
long long swapCount = 0;

void printArray(const std::vector<double>& v) 
{
    for (size_t i = 0; i < v.size(); i++) 
    {
        if (v[i] < 10) { std::cout << "0"; }
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}


int BinarySearch(std::vector<double>& T, int start, int end, double q)
{
    if (start > end) return -1;

    int pivot = start + (end - start)/2;

    compareCount++;
    if(std::abs(T[pivot] - q) < 1e-9) return pivot;
    
    compareCount++;
    if(T[pivot] < q)
    {
        return BinarySearch(T, pivot+1, end, q);
    }
    else 
    {
        return BinarySearch(T, start, pivot-1, q);
    }
}

int AlteredBinarySearch(std::vector<double>& T, int start, int end, double q)
{
    return BinarySearch(T, start, end, q);
}


int main()
{
    std::cout << std::fixed << std::setprecision(15);

    int n, func_num;
    double q;
    if (!(std::cin >> n >> q >> func_num)) return 0;

    std::vector<double> T(n);
    std::vector<double> original_T(n);

    for(int i = 0; i < n; i++)
    {   
        std::cin >> T[i];
        original_T[i] = T[i];
    }

    int start = 0;
    int end = n-1;
    double delta = 0.0;


    if(func_num == 1)
    {
        delta = 10.0;
        start = std::max(0, (int)std::floor(std::pow(2, std::cbrt(q - delta))) - 1);
        end = std::min(n - 1, (int)std::floor(std::pow(2, std::cbrt(q))) + 1);
    }
    else if (func_num == 2) 
    {
        delta = 50.0;
        double lower_val = std::max(0.0, q - delta - std::log2(n));
        start = std::min(n - 1, (int)std::floor(lower_val * lower_val));
        end = std::min(n - 1, (int)std::ceil(q * q));

        if (start > end) start = end;
    }



    compareCount = 0;
    (void)BinarySearch(T, 0, n-1, q);
    long long classic_cmp = compareCount;

    compareCount = 0;
    int altered_result = AlteredBinarySearch(T, start, end, q);
    long long altered_cmp = compareCount;

    if(n <= 30)
    {
        printArray(original_T);
        std::cout << "0\n";
        printArray(T);
        
        std::cout << altered_result << std::endl;

        if (altered_result == -1) 
        {
            std::cout << "NIE\n";
        }
        else 
        {
            std::cout << "TAK\n";
        }

        std::sort(original_T.begin(), original_T.end());
        printArray(original_T);
    }
    else 
    {
        std::cout << classic_cmp << "\n";
        std::cout << altered_cmp << "\n";
    }

    return 0;
}