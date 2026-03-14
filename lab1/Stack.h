#pragma once
#include <iostream>

class Node
{
  public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class Stack
{
private:
    Node* top = nullptr;
    int currentSize = 0;

public:
    Stack();
    ~Stack();

    void Push(int value);
    void Pop();
    int Size();
    bool Empty();
    void Display();

};