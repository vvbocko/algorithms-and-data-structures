#include <vector>
#include <random>
#include <ctime>
#include "CircularList.h"

std::mt19937 gen(time(nullptr));
std::uniform_int_distribution<> randDistribution(0, 100000);
std::uniform_int_distribution<> tableDistribution(0, 9999);

CircularList::CircularList() {}
CircularList::~CircularList()
{
    if (cursor == nullptr) 
    {
        return;
    }

    Node* current = cursor->next; 

    cursor->next = nullptr; 

    while (current != nullptr)
    {
        Node* nodeToDelete = current;
        current = current->next;
        delete nodeToDelete;
    }

    cursor = nullptr;
    currentSize = 0;
}

int CircularList::Size()
{
    return currentSize;
}

bool CircularList::Empty()
{
    return cursor == nullptr;
}

void CircularList::insert(int value)
{
    Node* newNode = new Node(value);

    if(cursor == nullptr)
    {
        newNode->next = newNode;
        cursor = newNode;
    }
    else
    {
        newNode->next = cursor->next; //zadzaiła ze wzgledu na kolejnośc - tutaj jeszcze cursor->next wskazuje sam na siebie
        cursor->next = newNode;
        cursor = newNode;
    }
    currentSize++;
}

void CircularList::merge(CircularList& list2)
{
    if(cursor == nullptr)
    {
        cursor = list2.cursor;
        currentSize = list2.currentSize;
        
        list2.cursor = nullptr; //wyzerowania
        list2.currentSize = 0;
        return;
    }
    if(list2.cursor == nullptr)
    {
        return;
    }

    Node* list1Begining = cursor->next; //1
    Node* list12Begining = list2.cursor->next; //4

    cursor->next = list12Begining;
    list2.cursor->next = list1Begining;

    currentSize += list2.currentSize;
    list2.currentSize = 0;

    cursor = list2.cursor;
    list2.cursor = nullptr;
}

    //          cursor         cursor
    //            v              v  
    // 1 -> 2  -> 3         4 -> 5
    // ^          |         ^    | 
    // |__________|         |____|



int CircularList::searchCost(int target)
{
    Node* temp = cursor;
    int comparisonCount = 0;

    if(Empty()) return 0;

    do
    {   
        comparisonCount++;

        if(temp->data != target)
        {
            temp = temp->next;
        }
        else
        {
            return comparisonCount;
        }
    } while(temp != cursor);

    return comparisonCount;
}

void CircularList::Display()
{
    if(Empty())
    {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node* start = cursor;
    while(start->next != cursor)
    {
        start = start->next;
        std::cout << start->data << ", ";
    }
    std::cout << start->next->data << std::endl;
}
    
int main()
{
    CircularList L;
    std::vector<int> T(10000);
    int sumRand = 0;
    int sumTable = 0;
    float average1 = 0.0f;
    float average2 = 0.0f;

    for(int i=0; i<=9999; i++)
    {   
        int randNumber = randDistribution(gen);  //losowa liczba z przedziału (0,100000)
        T[i] = randNumber;
    }
    for(int i=0; i<=9999; i++)
    {
        L.insert(T[i]);
    }
    
    for(int i=0; i<1000; i++)
    {
        int index = tableDistribution(gen); //losowa liczba z przedziału Tablicy T
        sumTable += L.searchCost(T[index]);
    }
    for(int i=0; i<1000; i++)
    {
        sumRand += L.searchCost(randDistribution(gen));
    }
    average1 = sumRand/1000.0f;
    average2 = sumTable/1000.0f;

    std::cout << "Sredni koszt (przedzial): \n";
    std::cout << average1 << std::endl;
    std::cout << "Sredni koszt (tablica): \n";
    std::cout << average2 << std::endl;

    CircularList list1;
    CircularList list2;

    std::cout << "\nLista 1: \n";
    for(int i=10; i<20; i++) //10-20
    {
        list1.insert(i);
        list1.Display();
    }

    std::cout << "\nLista 2: \n";
    for(int i=20; i<30; i++) //21 - 31
    {
        list2.insert(i);
        list2.Display();
    }

    std::cout << "\nMerge Listy 1 i Listy 2\n" << std::endl;
    list1.merge(list2);

    std::cout << "Lista 1: ";
    list1.Display();
    std::cout << "Lista 2: ";
    list2.Display();
}