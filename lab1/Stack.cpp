#include <iostream>
#include "Stack.h"


Stack::Stack() 
{

}

Stack::~Stack() 
{
    while(top != nullptr) 
    {
        Pop();
    }
}

void Stack::Push(int value) 
{
    Node* newNode = new Node(value);

    newNode->next = top;    // next nowego noda wskazuje tam gdzie wskaznik top
    top = newNode;          // wskaznik top wskazuje na newNode

    currentSize++;
}

void Stack::Pop() 
{
    if(Empty()) 
    {
        std::cout << "\nStack is empty";
        return;
    }
    Node* temp = top;
    top = top->next;
    delete temp;

    currentSize--;
}

int Stack::Size() 
{
    return currentSize;
}

bool Stack::Empty() 
{
    return top == nullptr;
}

void Stack::Display() 
{
    if(Empty()) 
    {
        std::cout << "\nDisplay stack:  Stack is empty\n";
        return;
    }

    Node* current = top;
    while(current->next != nullptr) 
    {
        std::cout << current->data << ", ";
        current = current->next;
    }
    std::cout << current->data << std::endl;
}

int main() 
{
    Stack stack;
    int maxSize = 50;

    stack.Display();
    std::cout << "Size:" << stack.Size() << std::endl;

    std::cout << "Add 50 elements:\n";
    for(int i=0; i<maxSize; i++)
    {
        stack.Push(i);
    }
    stack.Display();
    std::cout << "\nSize:" << stack.Size() << std::endl;

    std::cout << "Pop 51 element:\n";
    for(int i=0; i<maxSize+1; i++)
    {
        stack.Display();
        stack.Pop();
    }

    std::cout << "\nSize:" << stack.Size() << std::endl;
}