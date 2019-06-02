#include "rle.h"
#include "src/lzw.h"
#include <map>
#include <string>
#include <QMessageBox>
#include <fstream>
#include <vector>
using namespace std;

void CompressorRLE::compressRLE(QString &compressFileName, QString &rleFileName)
{
    ifstream fileInput(compressFileName.toStdString());
    ofstream fileCompressed(rleFileName.toStdString());
    char sym; //символ, который мы будем считывать
    int count=1;
    while (fileInput.good())
    {
        fileInput.get(sym);//считываем символ
        if (sym != fileInput.peek() || count == 9) // если символ не совпадает со следующим символом в файле
        {
            fileCompressed << count << sym; // записываем результаты в выходной файл
            count = 0;
        }
        count++;
    }
}

void CompressorRLE::decompressRLE(QString &compressedRLEfileName, QString &decompressedFileName)
{
    const char null = '0';
    ifstream fileToDescompress(compressedRLEfileName.toStdString());
    ofstream fileDecompressed(decompressedFileName.toStdString());

    char ch1, ch2;
    while(fileToDescompress.peek()!=EOF)
    {
        fileToDescompress.get(ch1);
        fileToDescompress.get(ch2);
        for (int i = 0; i < ch1 - null; i++)
            fileDecompressed << ch2;
    }
    fileToDescompress.close();
    fileDecompressed.close();
}


