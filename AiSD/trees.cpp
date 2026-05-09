#include <iostream>
#include <vector>


struct Node
{
    Node* L = nullptr;
    Node* R = nullptr;
    Node* Parent = nullptr;
    int value = 0;
};

void Insert_BST(Node*& root, int val)
{
    Node* newNode = new Node();

    if(root == nullptr) 
    {
        root = newNode;
        root->value = val;
        return;
    }

    Node* current = root;
    newNode->value = val;

    while(true)
    {
        if(current->value > val)
        {
            if(current->L != nullptr)
            {
                current = current->L;
            }
            else 
            {
                current->L = newNode;
                newNode->Parent = current;
                return;
            }
        }
        else
        {
            if(current->R != nullptr)
            {
                current = current->R;
            }
            else 
            {
                current->R = newNode;
                newNode->Parent = current;
                return;
            }
        }
    }
}



int main()
{
    Node* root = nullptr;
    Insert_BST(root, 15);
    Insert_BST(root, 10);
    Insert_BST(root, 20);
    Insert_BST(root, 11);

    std::cout << "Korzen: " << root->value << std::endl;
    std::cout << "Lewe dziecko korzenia: " << root->L->value << std::endl;
    std::cout << "Prawe dziecko korzenia: " << root->R->value << std::endl;
    std::cout << "Prawe dziecko korzenia: " << root->L->R->value << std::endl;
}