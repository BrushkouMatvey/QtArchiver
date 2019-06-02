#include "src/lzw.h"
#include <map>
#include <string>
#include <QString>
#include <QMessageBox>
#include <fstream>
using namespace std;


void CompressorLZW::readAllBytestextFile(QString &fileName, vector<char> &info)
{
    ifstream file(fileName.toStdString(), ios::binary | ios::ate);
    if (file.is_open())
    {
        ifstream::pos_type pos = file.tellg();
        info.resize(pos);
        file.seekg(0, ios::beg);
        file.read(&info[0], pos);
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Warning, "Error", "Unable to open file");
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        msgBox.exec();
    }
    file.close();
}

void CompressorLZW::writeCompressDataLZW(QString &fileName, vector<int> &info)
{
    ofstream file(fileName.toStdString(), ios::binary);
    if (file.is_open())
    {
        file.write((char*)&info[0], info.size() * sizeof(int));
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Warning, "Error", "Unable to open file");
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        msgBox.exec();
    }
    file.close();
}

void CompressorLZW::createTableLZWcompress(map<string, int> &table)
{
    for(int i = 0; i <= 255; i++)
    {
        string str = "";
        str += char(i);
        table[str] = i;
    }
}

void CompressorLZW::compressLZW(QString &compressFileName, QString &lzwFileName)
{
    map<string, int> table;
    vector<char> info;
    string p = "";
    string c = "";
    readAllBytestextFile(compressFileName, info);
    createTableLZWcompress(table);


    p += info[0];
    int code = table.size();
    vector<int> compressData;
    for (int i = 0; i < info.size(); i++)
    {
        if (i != info.size() - 1)
            c += info[i + 1];
        if (table.find(p + c) != table.end())
        {
            p = p + c;
        }
        else
        {
            compressData.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    compressData.push_back(table[p]);
    writeCompressDataLZW(lzwFileName, compressData);
}

void CompressorLZW::decompressLZW(QString &lzwFileName, QString &decompressFileName)
{
    ofstream file(decompressFileName.toStdString());
    map<int, string> table;
    vector<int> codes;
    readAllBytesFromLzwFile(lzwFileName, codes);
    createTableLZWdecompress(table);

    int oldCode = codes[0];
    string resStr = table[oldCode];
    string inputChar = "";
    inputChar += resStr[0];
    file<<resStr;

    int code = table.size();
    int n;
    for(int i = 0; i < codes.size() - 1; i++)
    {
        n = codes[i + 1];
        if(table.find(n) == table.end())
        {
            resStr = table[oldCode];
            resStr = resStr + inputChar;
        }
        else
        {
            resStr = table[n];
        }
        file<<resStr;
        inputChar = "";
        inputChar += resStr[0];
        table[code] = table[oldCode] + inputChar;
        code++;
        oldCode = n;
    }
    file.close();
}

void CompressorLZW::createTableLZWdecompress(map<int, string> &table)
{
    for (int i = 0; i <= 255; i++)
    {
        string str = "";
        str += char(i);
        table[i] = str;
    }
}

void CompressorLZW::readAllBytesFromLzwFile(QString &fileName, vector<int> &info)
{

    ifstream file(fileName.toStdString(), ios::binary | ios::ate);
    if (file.is_open())
    {
        ifstream::pos_type pos = file.tellg();
        info.resize(pos);
        file.seekg(0, ios::beg);
        file.read((char*)&info[0], pos);
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Warning, "Error", "Unable to open file");
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        msgBox.exec();
    }
    file.close();
}
