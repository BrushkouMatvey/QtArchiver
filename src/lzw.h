#ifndef LZW_H
#define LZW_H

#include <QString>
#include <map>
#include <string>
#include <vector>
class CompressorLZW
{
public:
    void writeCompressDataLZW(QString &fileName, std::vector<int> &info);
    void compressLZW(QString &compressFileName, QString &lzwFileName);
    void static readAllBytestextFile(QString &fileName, std::vector<char> &info);
    void decompressLZW(QString &lzwFileName, QString &decompressFileName);
    //void decompressHuffman(QString &lzwFileName, QString &decompressFileName);
    void readAllBytesFromLzwFile(QString &fileName, std::vector<int> &info);
    void createTableLZWcompress(std::map <std::string, int> &table);
    void createTableLZWdecompress(std::map<int, std::string> &table);
private:
};



#endif // LZW_H
