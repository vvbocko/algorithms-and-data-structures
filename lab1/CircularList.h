#pragma once
#include <iostream>

struct Node 
{
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr){};
};

struct CircularList
{
private:
    Node* cursor = nullptr;
    int currentSize = 0;

public:
    CircularList();  
    ~CircularList(); 

    void insert( int value);                 //wstawiającą nowy element z liczbą i do listy l,
    void merge(CircularList& list2);         //łączącą dwie listy l1, l2 i zademonstruj jej działanie dla list długości 10 zawierających dwucyfrowe liczby nieujemne.
    int searchCost(int target);          // losująca liczbę od 0 do threashold = target, przechodzi przez CircularList porównując każdą z liczb do target

    int Size();
    bool Empty();
    void Display();
};