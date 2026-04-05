#include <iostream>
#include <vector>

int compareCount = 0;
int swapCount = 0;

bool isLessOrEqual(int a, int b)
{
    compareCount++;
    return a <= b;
}

void copyElement(int& dest, int src)
{
    swapCount++;
    dest = src;
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

void Merge(std::vector<int>& v, std::vector<int>& temp, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if(isLessOrEqual(v[i], v[j]))
        {
            copyElement(temp[k], v[i]);
            i++;
            k++;
        }
        else
        {
            copyElement(temp[k], v[j]);
            j++;
            k++;
        }
    }

    while (i <= mid) 
    {
        copyElement(temp[k++], v[i++]);
    }
    while (j <= right)
    {
        copyElement(temp[k++], v[j++]);
    }

    
    for (i = left; i <= right; i++)
    {
        copyElement(v[i], temp[i]);
    }
}


void MergeSort(std::vector<int>& v, std::vector<int>& temp, int left, int right) 
{
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    
    MergeSort(v, temp, left, mid);
    MergeSort(v, temp, mid + 1, right);
    
    Merge(v, temp, left, mid, right);
    if (v.size() < 40) printArray(v);
}


int main()
{
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::vector<int> original_v(n);
    std::vector<int> temp(n);

    for(int i = 0; i < n; i++)
    {   
        std::cin >> v[i];
        original_v[i] = v[i];
    }

    if(n < 40) printArray(original_v);
    
    MergeSort(v, temp, 0, n - 1);

    if(n < 40)
    {
        printArray(original_v);
        std::cout << "0\n";
        printArray(v);
    }

    std::cout << compareCount << "\n";
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
    if(isSorted) {std::cerr << "Posortowano poprawnie\n";}
    else {std::cerr << "Blad sortowania\n";}
    return 0;
}