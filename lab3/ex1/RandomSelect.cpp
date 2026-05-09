#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

int compareCount = 0;
int swapCount = 0;

void printArray(const std::vector<int>& v) 
{
    for (size_t i = 0; i < v.size(); i++) 
    {
        if (v[i] < 10) { std::cout << "0"; }
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}


int PARTITION(std::vector<int>& T, int start, int end)
{
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);
    std::uniform_int_distribution<> randDistribution(start, end);

    swapCount++;
    std::swap(T[end], T[randDistribution(gen)]);

    int pivot = end;
    int i = start;

    for(int j = i; j < end; j++)
    {
        compareCount++;
        if(T[j] < T[pivot])
        {
            swapCount++;
            std::swap(T[i], T[j]);
            i++;
        }
    }

    swapCount++;
    std::swap(T[i], T[pivot]);

    if (T.size() <= 30) 
    {
        std::cout << "pivot=" << T[i] << "\n";
        printArray(T);
    }

    return i;
}

int RandomSelect(std::vector<int>& T, int start, int end, int k)
{
    if(start == end) return T[start];

    int new_pivot = PARTITION(T, start, end);

    if(new_pivot > k)
    {
        return RandomSelect(T, start, new_pivot-1, k);
    }
    else if(new_pivot < k)
    {
        return RandomSelect(T, new_pivot+1, end, k);
    }

    return T[new_pivot];  
}

int main() 
{
    int n, k_input;
    std::cin >> n >> k_input;


    std::vector<int> T(n);
    std::vector<int> original_T(n);

    for(int i = 0; i < n; i++)
    {   
        std::cin >> T[i];
        original_T[i] = T[i];
    }
    
    int start = 0;
    int end = n-1;
    int k = k_input - 1;
    int median_of_medians = RandomSelect(T, start, end, k);

    if(n <= 30)
    {
        printArray(original_T);
        std::cout << "0\n";
        printArray(T);
        
        std::cout << median_of_medians << std::endl;

        std::sort(original_T.begin(), original_T.end());
        printArray(original_T);
    }

    std::cout << compareCount <<"\n";
    std::cout << swapCount << "\n";

    return 0;
}   