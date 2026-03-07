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
    if (head == nullptr) 
    {
        std::cout << "\n Pop error:  Queue is empty\n";
        return;
    }
    
    Node* temp = head;
    std::cout << "Popping: " << temp->data << "\n";
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
        std::cout << "\n Display error:  Queue is empty\n";
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

    for(int i=0; i<maxSize; i++)
    {
        queue.Push(i);
    }
    queue.Display();
    std::cout << "Size:" << queue.Size() << std::endl;

    for(int i=0; i<maxSize+1; i++)
    {
        queue.Pop();
        queue.Display();
    }
    std::cout << "Size:" << queue.Size() << std::endl;
}