#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int compareCount = 0;
int swapCount = 0;

bool isGreater(int a, int b)
{
    compareCount++;
    return a > b;
}

void swapKeys(int& a, int& b)
{
    swapCount++;
    std::swap(a, b);
}

void InsertionSort(std::vector<int>& v) 
{
    for(size_t i=1; i<v.size(); i++)
    {
        int j = i;
        while (j > 0 && isGreater(v[j-1], v[j])) 
        {
            swapKeys(v[j-1], v[j]);
            j--;
        }
    }
}

int main() 
{
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::vector<int> original_v(n);

    for(int i = 0; i < n; i++)
    {   
        std::cin >> v[i];
        original_v[i] = v[i];
    }
    
    InsertionSort(v);

    std::cout << compareCount <<"\n";
    std::cout << swapCount << "\n";

    bool isSorted = true;
    for(int i=1; i<n; i++)
    {
        if(v[i-1] > v[i])
        {
            isSorted = false;
            break;
        }
    }
    if(!isSorted) {std::cerr << "Blad sortowania\n";}
    
    return 0;
}