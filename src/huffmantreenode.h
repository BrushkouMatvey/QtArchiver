#ifndef HUFFMANTREENODE_H
#define HUFFMANTREENODE_H
class Node
{
public:
    Node *left;
    Node *right;
    int count;
    char symbol;

    Node(){}

    Node(char symbol, int count)
    {
        this->count = count;
        this->symbol = symbol;
        this->left = nullptr;
        this->right = nullptr;
    }

    Node(Node *left, Node *right)
    {
        this->symbol = 0;
        this->left = left;
        this->right = right;
        count = left->count + right->count;
    }
};

#endif // HUFFMANTREENODE_H
