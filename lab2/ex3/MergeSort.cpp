// Zadanie 3. [30 p.]
// Wykonaj eksperymenty analogiczne do zadań 1 i 2 dla wymyślonego przez siebie algorytmu sortowania, który:
// 1. Używa metodologii D&C (dziel i zwyciężaj).
// 2. Wykorzystuje procedurę Merge z MergeSorta.
// 3. Do scalania będzie wykorzystywać aktualnie istniejące w danych wejściowych spójne podciągi rosnące. Taka idea jest użyta również w TimSorcie i PowerSorcie linki tutaj:
//      a. https://en.wikipedia.org/wiki/Timsort
//      b. https://youtu.be/exbuZQpWkQ0?feature=shared
//      c. https://www.wild-inter.net/publications/munro-wild-2018.pdf
// 4. Twoim głównym zadaniem jest wymyślenie i zaimplementowanie zasad scalania znalezionych podciągów, które będą maksymalizować efektywności stworzonego algorytmu.
// 5. Porównaj na wykresie wyniki swojego algorytmu z klasycznym MergeSort'em.

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
}