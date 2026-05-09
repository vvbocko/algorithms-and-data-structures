#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

long long compareCount = 0;
long long swapCount = 0;

void compare() 
{ 
    compareCount++; 
}

void swapKeys(int& a, int& b)
{ 
    swapCount++; 
    std::swap(a, b); 
}

int InsertionSort(std::vector<int>& tab, int start, int end) 
{
    for(int i = start+1; i <= end; i++) 
    {
        int key = tab[i];
        int j = i - 1;
        while (j >= start) 
        {
            compare();
            if (tab[j] > key) 
            {
                swapCount++;
                tab[j+1] = tab[j];
                j--;
            } else {
                break;
            }
        }
        tab[j+1] = key;
    }
    int mid = start + (end - start) / 2;
    return tab[mid];
}

int PARTITION(std::vector<int>& T, int start, int end, int p_value) 
{
    int i = start;
    while(i <= end && T[i] != p_value) 
    {
        i++;
    }
    swapKeys(T[i], T[end]);

    int pivot = end;
    i = start;

    for(int j = start; j < end; j++) 
    {
        compare();
        if(T[j] < T[pivot]) 
        {
            swapKeys(T[i], T[j]);
            i++;
        }
    }
    swapKeys(T[i], T[pivot]);
    return i;
}

int SELECT(std::vector<int>& T, int start, int end, int k, int group_size)
{
    if (start == end)
    {
        return T[start];
    }

    std::vector<int> M;

    for(int i = start; i <= end; i += group_size)
    {
        int L = i;
        int R = std::min(i + group_size - 1, end);
        M.push_back(InsertionSort(T, L, R));
    }

    int p_value = 0;
    if(M.size() == 1)
    {
        p_value = M[0];
    } 
    else
    {
        p_value = SELECT(M, 0, M.size()-1, M.size()/2, group_size);
    }

    int new_pivot = PARTITION(T, start, end, p_value);

    if(new_pivot < k)
    {
        return SELECT(T, new_pivot+1, end, k, group_size);
    }
    else if(new_pivot > k)
    {
        return SELECT(T, start, new_pivot-1, k, group_size);
    }

    return T[new_pivot];
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Podaj rozmiar grupy!\n";
        return 1;
    }
    int group_size = std::stoi(argv[1]);

    int n, k_input;
    if (!(std::cin >> n >> k_input)) return 0;

    std::vector<int> T(n);
    for(int i = 0; i < n; i++)
    {
        std::cin >> T[i];
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    
    int result = SELECT(T, 0, n-1, k_input, group_size);
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << result << "\n";
    std::cout << compareCount << "\n";
    std::cout << swapCount << "\n";
    std::cout << duration.count() << "\n";

    return 0;
}