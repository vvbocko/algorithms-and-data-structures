#pragma once
#include <iostream>

struct Node 
{
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr){};
};

struct DoublyCircularList
{
private:
    Node* cursor = nullptr;
    int currentSize = 0;

public:
    DoublyCircularList();  
    ~DoublyCircularList(); 

    void insert( int value);                        //wstawiającą nowy element z liczbą i do listy l,
    void merge(DoublyCircularList& list2);          //łączącą dwie listy l1, l2 i zademonstruj jej działanie dla list długości 10 zawierających dwucyfrowe liczby nieujemne.
    int searchCost(int target);                     // losująca liczbę od 0 do threashold = target, przechodzi przez CircularList porównując każdą z liczb do target

    int Size();
    bool Empty();
    void Display();
};