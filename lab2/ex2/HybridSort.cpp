#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int threshold = 10;
int compareCount = 0;
int swapCount = 0;

bool isGreater(int a, int b)
{
    compareCount++;
    return a > b;
}

bool isLess(int a, int b) 
{
    compareCount++;
    return a < b;
}

void swapKeys(int& a, int& b)
{
    swapCount++;
    std::swap(a, b);
}

int HoarePartition(std::vector<int> &v, int low, int high)
{
    int pivot = v[(low + (high - low)/2)];

    int i = low - 1;
    int j = high + 1;

    while (true)
    {
        do 
        {
            i++;
        } while(isLess(v[i], pivot));
        
        do
        {
            j--;
        } while(isGreater(v[j], pivot));

        if(i >= j) return j;

        swapKeys(v[i], v[j]);
    }
}

void InsertionSort(std::vector<int>& v, int low, int high) 
{
    for(int i=low+1; i<=high; i++)
    {
        int j = i;
        while (j > low && isGreater(v[j-1], v[j]))
        {
            swapKeys(v[j-1], v[j]);
            j--;
        }
    }
}

void HybridSort(std::vector<int>& v, int low, int high, int n)
{
    if(low < high)
    {
       if(high-low + 1 <= threshold)
        {
            InsertionSort(v, low, high);
        }
        else
        {
            int partitionIndex = HoarePartition(v, low, high);

            HybridSort(v, low, partitionIndex, n);
            HybridSort(v, partitionIndex + 1, high, n);
        } 
    }
}

int main(int argc, char* argv[]) 
{
    if (argc > 1) 
    {
        threshold = std::stoi(argv[1]);
    }

    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::vector<int> original_v(n);

    for(int i = 0; i < n; i++)
    {   
        std::cin >> v[i];
        original_v[i] = v[i];
    }
    
    HybridSort(v, 0, n - 1, n);

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
    if(!isSorted) {std::cerr << "Blad sortowania!\n";}
    
    return 0;
}