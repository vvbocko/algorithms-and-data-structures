#include <vector>
#include <random>
#include <ctime>
#include "DoublyCircularList.h"

std::mt19937 gen(time(nullptr));
std::uniform_int_distribution<> randDistribution(0, 100000);
std::uniform_int_distribution<> tableDistribution(0, 9999);
std::uniform_int_distribution<> directionDistribution(0, 1);


DoublyCircularList::DoublyCircularList() {}
DoublyCircularList::~DoublyCircularList()
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

int DoublyCircularList::Size()
{
    return currentSize;
}

bool DoublyCircularList::Empty()
{
    return cursor == nullptr;
}

void DoublyCircularList::insert(int value)
{
    Node* newNode = new Node(value);

    if(cursor == nullptr)
    {
        newNode->next = newNode;
        newNode->prev = newNode;

        cursor = newNode;
    }
    else 
    {
        newNode->next = cursor->next; //= head;
        newNode->prev = cursor;

        cursor->next->prev = newNode; //head->prev =
        cursor->next = newNode;

        cursor = newNode;
    }
    currentSize++;
}

void DoublyCircularList::merge(DoublyCircularList& list2)
{
    if(cursor == nullptr)
    {
        cursor = list2.cursor;
        currentSize = list2.currentSize;

        list2.cursor = nullptr;
        list2.currentSize = 0;

        return;
    }
    if(list2.cursor == nullptr)
    {
        return;
    }

    Node* list1head = cursor->next;
    Node* list2head = list2.cursor->next;

    cursor->next = list2head;
    list2.cursor->next = list1head;

    list1head->prev = list2.cursor;
    list2head->prev = cursor;

    currentSize += list2.currentSize;
    list2.currentSize = 0;

    cursor = list2.cursor;
    list2.cursor = nullptr;
}

int DoublyCircularList::searchCost(int target)
{
    Node* temp = cursor;
    int comparisonCount = 0;
    int direction = directionDistribution(gen);

    if(Empty()) return 0;

    do
    {   
        comparisonCount++;

        if(temp->data != target)
        {
            if(direction == 0)
            {
                temp = temp->next;
            }
            else
            {
                temp = temp->prev;
            }
        }
        else
        {
            return comparisonCount;
        }
    } while(temp != cursor);

    return comparisonCount;
}

void DoublyCircularList::Display()
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
    DoublyCircularList L;
    std::vector<int> T(10000);
    int sumRand = 0;
    int sumTable = 0;
    float average1 = 0.0f;
    float average2 = 0.0f;

    for(int i=0; i<=9999; i++)
    {   
        int randNumber = randDistribution(gen); //losowa liczba z przedziału (0,100000)
        T[i] = randNumber;
    }
    for(int i=0; i<=9999; i++)
    {
        L.insert(T[i]);
    }
    //search
    for(int i=0; i<1000; i++)
    {
        int index = tableDistribution(gen);  //losowa liczba z przedziału Tablicy T
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

    DoublyCircularList list1;
    DoublyCircularList list2;

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