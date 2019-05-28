#include "src/extract_window.h"
#include "ui_extract_window.h"
#include <QFileDialog>
#include <QMessageBox>
#include <map>
#include <string>
#include <fstream>
#include <QDebug>

using namespace std;

Extract_window::Extract_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Extract_window)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);//убираем кнопку с вопросом
}

Extract_window::~Extract_window()
{
    delete ui;
}

void Extract_window::on_BrowseButton_clicked()
{
    direct = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    this->ui->BrowseLineEdit->setText(direct);
}

void Extract_window::on_AppendButton_clicked()
{
    if(this->ui->LZWRadioButton->isChecked())
    {
        filesToDecompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to decompress","D:\\","LZW files (*.lzw)");
    }
    else
    {
        filesToDecompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to decompress","D:\\","HUF files (*.huf)");
    }
    pathsForQLineEdit = filesToDecompress.join(";");
    this->ui->AppendLineEdit->setText(pathsForQLineEdit);
}


void Extract_window::on_OK_clicked()
{
    if(this->ui->AppendLineEdit->text().isEmpty() ||
            this->ui->BrowseLineEdit->text().isEmpty())
    {
        QMessageBox msgBox(QMessageBox::Warning, "Error", "Error : empty fields");
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        msgBox.exec();
    }
    else
    {
        QDir dir(this->ui->BrowseLineEdit->text());
        if (!dir.exists())
        {
          dir.mkdir(".");
        }
        if(this->ui->LZWRadioButton->isChecked())
        {
            for(auto it:filesToDecompress)
            {
                QString tempDir = direct;
                QString lzwDecompressFileName = tempDir.append(it.split("/").back().split(".").front().append(".txt").prepend("/"));
                decompressLZW(it, lzwDecompressFileName);
            }
        }
        else
        {
            for(auto it:filesToDecompress)
            {
                QString tempDir = direct;
                QString huffmanDecompressFileName =  tempDir.append(it.split("/").back().split(".").front().append(".txt").prepend("/"));
                decompressHuffman(it, huffmanDecompressFileName);
            }
        }
    }
}

void Extract_window::decompressLZW(QString &lzwFileName, QString &decompressFileName)
{
    ofstream file(decompressFileName.toLocal8Bit().constData());
    map<int, string> table;
    vector<int> codes;
    readAllBytesFromLzwFile(lzwFileName, codes);
    createTableLZW(table);

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
}

void Extract_window::createTableLZW(map<int, string> &table)
{
    for (int i = 0; i <= 255; i++)
    {
        string str = "";
        str += char(i);
        table[i] = str;
    }
}

void Extract_window::readAllBytesFromLzwFile(QString fileName, vector<int> &info)
{

    ifstream file(fileName.toLocal8Bit().constData(), ios::binary | ios::ate);
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

void Extract_window::decompressHuffman(QString &lzwFileName, QString &decompressFileName)
{

}
