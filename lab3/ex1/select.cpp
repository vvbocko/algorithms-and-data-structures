#include <iostream>
#include <vector>
#include <limits>

//k-th index of an element we search for
int SELECT(std::vector<int> T, int start, int end, int k)
{
    // divide T into groups of 5
    //for every group find median
    // if 2 | group size ten median is a mean of two middle elems

    // take every mean from each group and add it to new vector MEDIANS

    // if MEDIANS.size <= 5 - treat it as a group (Insertion sort and get median - it will be a p_value)
    // else SELECT(MEDIANS, start = 0, end = MEDIANS.size -1, MEDIANS.size/2)

    //search for element with that p_value and that will be the pivot)

    //new_pivot = PARTITION(T, start, end, pivot)

    //if(new_pivot == k) return T[new_pivot];
    //else if(new_pivot < k) SELECT(T, new_pivot+1, end, k-new_pivot)
    //else if(new_pivot > k) SELECT(T, start, new_pivot-1, k)
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
    
    return 0;
}