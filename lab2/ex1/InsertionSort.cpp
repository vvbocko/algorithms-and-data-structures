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

void printArray(const std::vector<int>& v) 
{
    for (int i = 0; i < v.size(); i++) 
    {
        if (v[i] < 10) { std::cout << "0"; }
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

void InsertionSort(std::vector<int>& v) 
{
    for(int i=1; i<v.size(); i++)
    {
        int j = i;
        while (j > 0 && isGreater(v[j-1], v[j])) 
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

    if(n < 40)
    {
        printArray(original_v);
        // - tablica wejsciowa
        // - stany sortowanej tablicy w istotnych momentach (np. w MERGE SORT - po zakończeniu każdego scalania),
    }
    
    InsertionSort(v);

    if(n < 40)
    {
        // - tablicę wejściową (ponownie dla porównania!),
        printArray(original_v);
        std::cout << "0\n";
        // - tablicę po sortowaniu.
        printArray(v);
        //Dla czytelności drukujmy klucze jako liczby dwucyfrowe.
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
    if(isSorted) {std::cout << "Posortowano poprawnie.\n";}
    else {std::cerr << "Blad sortowania!\n";}
    
    return 0;
}