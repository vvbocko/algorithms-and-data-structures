#pragma once
#include <iostream>

class Node 
{
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr){};
};

class Queue 
{
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int currentSize = 0;

public:
    Queue();
    ~Queue();

    void Push(int value);
    void Pop();
    int Size();
    bool Empty();
    void Display();
};