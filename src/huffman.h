#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "src/huffmantreenode.h"
#include <QString>
#include <vector>
#include <map>

class CompressorHuffman
{
public:
    void Print(Node *root, int depth);
    void compressHuffman(QString &compressFileName, QString &hufFileName);
    void decompressHuffman(QString &hufFileName, QString &decompressFileName);
    void buildTable(Node *root);
    bool sortNode(const Node *a, const Node *b);
private:
    std::vector<bool> code;
    std::map<char, std::vector<bool>> table;
    static Node *root;
};
#endif // HUFFMAN_H
