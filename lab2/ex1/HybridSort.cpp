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

void printArray(const std::vector<int>& v) 
{
    for (size_t i = 0; i < v.size(); i++) 
    {
        if (v[i] < 10) { std::cout << "0"; }
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
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

        if(v.size() < 40)
        {
            printArray(v);
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
            
            if(n < 40) 
            {
                printArray(v);
            }

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

    if(n < 40)
    {
        printArray(original_v);
    }
    
    HybridSort(v, 0, n - 1, n);

    if(n < 40)
    {
        printArray(original_v);
        std::cout << "0\n";
        printArray(v);
    }

    // Dla dowolnego rozmiaru danych, na końcu:

    // - ○ łączną liczbę porównań między kluczami,
    std::cout << compareCount <<"\n";
    // - ○ łączną liczbę przestawień kluczy.
    std::cout << swapCount << "\n";

    // - (Zaimplementować osobne funkcje/procedury do porównywania i przestawiania kluczy, które dodatkowo zwiększają swój globalny licznik odpowiednio porównań lub przestawień.)
    //jest
    // - Finalnie, program sam sprawdza, czy wynikowy ciąg jest posortowanym ciągiem wejściowym.
    bool isSorted = true;
    for(int i=1; i<n; i++)
    {
        if(v[i-1] > v[i])
        {
            isSorted = false;
            break;
        }
    }
    if(isSorted) {std::cerr << "Posortowano poprawnie.\n";}
    else {std::cerr << "Blad sortowania!\n";}
    
    return 0;
}