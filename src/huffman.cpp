#include "src/huffman.h"
#include "src/lzw.h"
#include "src/huffmantreenode.h"
#include <list>
#include <fstream>
#include <QDebug>
using namespace std;

Node *CompressorHuffman::root = nullptr;

struct Compare
{
    bool operator()(Node* left, Node* right) const
    {
        return left->count < right->count;
    }
};

void CompressorHuffman::Print(Node *root, int depth)
    {
        if (!root) return;

        if (root->symbol)
        {
            for (int i = 0; i < depth; i++)
                qDebug() << ".";
            qDebug() << root->symbol << endl;
        }
        else depth++;
        Print(root->left, depth);
        Print(root->right, depth);
    }

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

    buildTable(this->root);
    ifstream fileCodes(compressFileName.toStdString());
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

void CompressorHuffman::buildTable(Node *root)
{

    if (root->left!=nullptr)
    {
        code.push_back(0);
        buildTable(root->left);
    }

    if (root->right!=nullptr)
    {
        code.push_back(1);
        buildTable(root->right);
    }

    if (root->left==nullptr && root->right==nullptr)
        table[root->symbol]=code;
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
        if(p->left == nullptr && p->right == nullptr)
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


