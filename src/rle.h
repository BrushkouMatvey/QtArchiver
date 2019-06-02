#ifndef RLE_H
#define RLE_H
#include <QString>


class CompressorRLE
{
public:
    void compressRLE(QString &compressFileName, QString &lzwFileName);
    void decompressRLE(QString &compressedRLE, QString &decompressedFileName);
};

#endif // RLE_H
