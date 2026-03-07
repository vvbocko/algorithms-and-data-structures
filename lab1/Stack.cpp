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
    if(top == nullptr) 
    {
        std::cout << "Stack is empty\n";
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
    if(top == nullptr) 
    {
        std::cout << "Stack is empty\n";
        return;
    }

    Node* current = top;
    while(current->next != nullptr) 
    {
        std::cout << current->data << ", ";
        current = current->next;
    }
    std::cout << current->data;
}

int main() 
{
    Stack stack;

    for(int i=0; i<50; i++)
    {
        stack.Push(i);
    }
    stack.Display();
}

