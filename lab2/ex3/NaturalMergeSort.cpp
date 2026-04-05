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

void MergeRuns(std::vector<int>& v, std::vector<int>& temp, const std::vector<std::pair<int, int>>& runs, int run_left, int run_right) 
{
    if (run_left >= run_right) return;

    int run_mid = run_left + (run_right - run_left) / 2;
    
    MergeRuns(v, temp, runs, run_left, run_mid);
    MergeRuns(v, temp, runs, run_mid + 1, run_right);
    
    int left = runs[run_left].first;
    int mid = runs[run_mid].second;
    int right = runs[run_right].second;
    
    Merge(v, temp, left, mid, right);
    // if (v.size() < 40) printArray(v);
}

void NaturalMergeSort(std::vector<int>& v, std::vector<int>& temp, int n) // dziel i zwyciężaj + Merge() + podział na runs - wzrastające
{
    std::vector<std::pair<int, int>> runs;
    // znaleźć rosnące 
    int start = 0;

    for (int i=0; i<n-1; i++)
    {
        if (!isLessOrEqual(v[i], v[i+1]))
        {
            runs.push_back({start, i}); // wektor początku i końca posortowanego już ciagu
            start = i + 1;
        }
    }
    runs.push_back({start, n - 1});

    if (runs.size() > 1) 
    {
        MergeRuns(v, temp, runs, 0, runs.size() - 1);
    }
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

    // if(n < 40) printArray(original_v);
    
    NaturalMergeSort(v, temp, n);

    // if(n < 40)
    // {
    //     printArray(original_v);
    //     std::cout << "0\n";
    //     printArray(v);
    // }

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
    if(!isSorted) {std::cerr << "\n";}
    return 0;
}