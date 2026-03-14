#include "Queue.h"

Queue::Queue() {}

Queue::~Queue()
{
    while(head != nullptr)
    {
        Pop();
    }
}

void Queue::Push(int value)
{
    Node* newNode = new Node(value);
    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else 
    {
        tail->next = newNode;
        tail = newNode;
    }
    currentSize++;
}
// head;         tail
// v              v
// 1 -> 2 -> 3 -> 4

void Queue::Pop()
{
    if (Empty()) 
    {
        std::cout << "\nPop error:  Queue is empty\n";
        return;
    }
    
    Node* temp = head;
    if(head->next == nullptr)
    {
        tail = nullptr;
    }

    head = head->next;
    delete temp;

    currentSize--;
}

int Queue::Size()
{
    return currentSize;
}

bool Queue::Empty()
{
    return head == nullptr;
}

void Queue::Display()
{
    if (Empty()) 
    {
        std::cout << "\nDisplay error:  Queue is empty\n";
        return;
    }

    Node* current = head;
    while (current->next != nullptr)
    {
        std::cout << current->data << ", ";
        current = current->next;
    }
    std::cout << current->data << std::endl;
}

int main() 
{
    Queue queue;
    int maxSize = 50;

    queue.Display();
    std::cout << "Size:" << queue.Size() << std::endl;
    std::cout << "Add 50 elements:\n";
    for(int i=0; i<maxSize; i++)
    {
        queue.Push(i);
    }
    queue.Display();
    std::cout << "\nSize:" << queue.Size() << std::endl;

    std::cout << "Pop 51 elements:\n";
    for(int i=0; i<maxSize+1; i++)
    {
        queue.Display();
        queue.Pop();
    }
    std::cout << "Size:" << queue.Size() << std::endl;
}