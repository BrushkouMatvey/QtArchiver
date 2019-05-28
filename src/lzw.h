#ifndef LZW_H
#define LZW_H

#include <QString>
#include <map>
#include <string>
#include <vector>

void writeCompressDataLZW(QString &fileName, std::vector<int> &info);
void compressLZW(QString &compressFileName, QString &lzwFileName);
void readAllBytesLZWtextFile(QString &fileName, std::vector<char> &info);
void decompressLZW(QString &lzwFileName, QString &decompressFileName);
void decompressHuffman(QString &lzwFileName, QString &decompressFileName);
void readAllBytesFromLzwFile(QString &fileName, std::vector<int> &info);
void createTableLZWcompress(std::map <std::string, int> &table);
void createTableLZWdecompress(std::map<int, std::string> &table);

#endif // LZW_H
