#include "src/huffman.h"
#include "src/lzw.h"
#include "src/huffmantreenode.h"
#include <list>
#include <fstream>
#include <QDebug>
using namespace std;

struct Compare
{
    bool operator()(Node* left, Node* right) const
    {
        return left->count < right->count;
    }
};

void CompressorHuffman::compressHuffman(QString &compressFileName, QString &hufFileName)
{
    vector<char> info;
    CompressorLZW::readAllBytestextFile(compressFileName, info);
    map<char, int> symbols;
    for(auto it : info)
    {
        symbols[it]++;
    }

    list<Node*> tree;
    map<char, int>::iterator it;
    for (it = symbols.begin(); it != symbols.end(); it++)
    {
        Node *p = new Node(it->first, it->second); // key = symbol;  value = count
        tree.push_back(p);
    }

    while(tree.size() != 1)
    {
        tree.sort(Compare());

        Node *tmp1 = tree.front();
        tree.pop_front();
        Node *tmp2 = tree.front();
        tree.pop_front();

        Node *parent = new Node(tmp1, tmp2);
        tree.push_back(parent);
    }
    this->root = tree.front();

    vector<bool> code;
    map<char, vector<bool>> table;
    buildTable(this->root, code, table);
    ifstream fileCodes("codes.txt");
    ofstream fileCompressed(hufFileName.toStdString());
    int count; char buffer = 0;
    while(!fileCodes.eof())
    {
        char ch;
        ch = fileCodes.get();
        vector<bool> x = table[ch];
        for(int i = 0; i < x.size(); i++)
        {
            buffer = buffer | x[i]<<(7-count);
            count++;
            if(count == 8)
            {
                count = 0;
                fileCompressed << buffer;
                buffer = 0;
            }
        }
    }
    fileCodes.close();
    fileCompressed.close();
}

void CompressorHuffman::buildTable(Node *root, std::vector<bool> &code, std::map<char, std::vector<bool>> &table)
{
    if (root->left)
    {
        code.push_back(0); // left
        buildTable(root->left, code, table);
    }
    if (root->right)
    {
        code.push_back(1); // right
        buildTable(root->right, code, table);
    }
    if (root->right == NULL && root->left == NULL)
        table[root->symbol] = code;
        code.pop_back();
}

bool CompressorHuffman::sortNode(const Node *a, const Node *b)
{
    return a->count < b->count;
}

void CompressorHuffman::decompressHuffman(QString &hufFileName, QString &decompressFileName)
{
    ifstream file(hufFileName.toStdString());
    ofstream decompressFile(decompressFileName.toStdString());
    Node *p = this->root;
    int count = 0;
    char byte;
    byte = file.get();

    while(!file.eof())
    {
        bool b = byte &(1 << (7 - count));
        if(b)
            p = p->right;
        else
            p = p->left;
        if(p->left == NULL && p->right == NULL)
        {
            decompressFile<<p->symbol;
            p = root;
        }
        count++;
        if(count == 8)
        {
            count = 0;
            byte = file.get();
        }
    }
    file.close();
    decompressFile.close();
}


