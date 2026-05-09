#include <iostream>
#include <vector>
#include <limits>

double Mediana1(const std::vector<double>& X, const std::vector<double>& Y)
{
    int n = X.size();

    int i = 0;
    int j = 0;
    double mediana = 0;
    double a = 0;
    double b = 0;
    
    for (int k = 0; k < n-1; k++)
    {
        if(X[i] < Y[j])
        {
            i++;
        }
        else j++;
    }
    if(X[i] < Y[j])
    {
        a = X[i];
        i++;
    }
    else 
    {
        a = Y[j];
        j++;
    }
    //sprawdzić czy nie wychodzi poza tablice
    if(X[i] < Y[j])
    {
        b = X.at(i);
        i++;
    }
    else 
    {
        b = Y[j];
        j++;
    }
    mediana = (a + b)/2;
    return mediana;
}


double Mediana2(const std::vector<double>& X, const std::vector<double>& Y)
{
    int n = X.size();
    int left = 0; // minimalna licz elementów z tab X
    int right = n; // maksymalna licz elementów z tab X

    while (left <= right)
    {
        int k1 = (left + right)/2; // tyle początkowych elementów bierzemy z tab X
        int k2 = n - k1; // tyle początkowych elementów bierzemy z tab Y

        
        double a = (k1 > 0 ? X.at(k1-1) : -std::numeric_limits<double>::infinity());
        double b = (k1 < n ? X.at(k1) : std::numeric_limits<double>::infinity());
        double c = (k2 > 0 ? Y.at(k2-1) : -std::numeric_limits<double>::infinity());
        double d = (k2 < n ? Y.at(k2) : std::numeric_limits<double>::infinity());

        if(a <= d && c <= b)
        {
            return (std::max(a,c) + std::min(b,d))/2;
        }
        else if (a > d)
        {
            right = k1-1;
        }
        else if(c > b)
        {
            left = k1 + 1;
        }
    }
    
}

std::vector<double> Merge(const std::vector<double>& X, const std::vector<double>& Y)
{
    std::vector<double> temp(X.size() + Y.size());
    int i = 0;
    int j = 0;
    int k = 0;
    int liczba_inwersji = 0;

    while (i < X.size() && j < Y.size())
    {
        if(X[i] <= Y[j])
        {
            temp[k++] = X[i++];
        }
        else 
        {
            temp[k++] = Y[j++];
            liczba_inwersji += X.size() - i;
        }
    }
    while (i < X.size())
    {

        temp[k++] = X[i++];

    }
    while (j < Y.size())
    {
        temp[k++] = X[i++];
    }

    return temp;
    //zwraca liczba_inwersji
}




int main()
{
    std::cout << Mediana2({1,2,3,4,5}, {6,7,8,9,10});

    //std::cout << Mediana2({1,3,6,10,14}, {2,4,7,12,15});
}
