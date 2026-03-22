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

int main() 
{
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::vector<int> original_v(n);

    
    for(int i = 0; i < n; i++)
    {   
        std::cin >> v[i];
    }

    for(int i = 0; i < n; i++)
    {   
        original_v[i] = v[i];
    }

    if(n < 40)
    {
        // - tablica wejsciowa
        for(int i=0; i<n; i++)
        {
            if(v[i]<10) { std::cout <<"0"; }
            std::cout << original_v[i] <<" ";
        }
        std::cout << "\n";
        // - stany sortowanej tablicy w istotnych momentach (np. w MERGE SORT - po zakończeniu każdego scalania),
    }
    
    for(int i=1; i<n; i++)
    {
        int j = i;
        while (j > 0 && isGreater(v[j-1], v[j])) 
        {
            swapKeys(v[j-1], v[j]);
            j--;
        }

        if(n < 40)
        {
            for(int i=0; i<n; i++)
            {
                if(v[i]<10) { std::cout <<"0"; }
                std::cout << v[i] <<" ";
            }
            std::cout << "\n";
        }
    }

    if(n < 40)
    {
        // - tablicę wejściową (ponownie dla porównania!),
        for(int i=0; i<n; i++)
        {
            if(original_v[i]<10) { std::cout <<"0"; }
            std::cout << original_v[i] <<" ";
        }
        std::cout << "\n";
        std::cout << "0\n";
        // - tablicę po sortowaniu.
        for(int i=0; i<n; i++)
        {
            if(v[i]<10) { std::cout <<"0"; }
            std::cout << v[i] <<" ";
        }
        //Dla czytelności drukujmy klucze jako liczby dwucyfrowe.
        std::cout << "\n";
    }

    // Dla dowolnego rozmiaru danych, na końcu:

    // - ○ łączną liczbę porównań między kluczami,
    std::cout << compareCount <<"\n";
    // - ○ łączną liczbę przestawień kluczy.
    std::cout << swapCount << "\n";

    // - (Zaimplementować osobne funkcje/procedury do porównywania i przestawiania kluczy, które dodatkowo zwiększają swój globalny licznik odpowiednio porównań lub przestawień.)
    //jest
    // - Finalnie, program sam sprawdza, czy wynikowy ciąg jest posortowanym ciągiem wejściowym.
    for(int i=1; i<n; i++)
    {
        if(v[i-1] > v[i])
        {
            std::cout << "Dane nie są posortowane. \n";
        }
    }
    std::cout << "\n";
    return 0;
}