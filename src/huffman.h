#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "src/huffmantreenode.h"
#include <QString>
#include <vector>
#include <map>

class CompressorHuffman
{
public:
    void compressHuffman(QString &compressFileName, QString &hufFileName);
    void decompressHuffman(QString &hufFileName, QString &decompressFileName);
    void buildTable(Node *root, std::vector<bool> &code, std::map<char, std::vector<bool>> &table);
    bool sortNode(const Node *a, const Node *b);
private:
    Node *root;
};
#endif // HUFFMAN_H
