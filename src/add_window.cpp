#include "src/add_window.h"
#include "ui_add_window.h"
#include "src/compressor.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <fstream>
#include <vector>
#define SPACE ' '
using namespace std;

Add_window::Add_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_window)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);//убираем кнопку с вопросом
}

Add_window::~Add_window()
{
    delete ui;
}


void Add_window::on_BrowseButton_clicked()
{
    direct = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    this->ui->BrowseLineEdit->setText(direct);
}

void Add_window::on_AppendButton_clicked()
{
    if(this->ui->LZWRadioButton->isChecked())
        filesToCompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to archive","D:\\","Text Files (*.txt *.cpp *.h *.rtf)");
    else
        filesToCompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to archive","D:\\","Images (*.jpg *.png)");

    pathsForQLineEdit = filesToCompress.join(";");
    this->ui->AppendLineEdit->setText(pathsForQLineEdit);
}

void Add_window::on_Ok_clicked()
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
        if (!dir.exists()){
          dir.mkdir(".");
        }

        if(this->ui->LZWRadioButton->isChecked())
        {
            for(auto it:filesToCompress)
            {
                QString tempDir = direct;
                QString lzwFileName = tempDir.append(it.split(":").back().split(".").front().append(".lzw"));
                compressLZW(it, lzwFileName);
            }
        }
        else
        {
            for(auto it:filesToCompress)
            {
                QString tempDir = direct;
                QString huffmanFileName = tempDir.append(it.split(":").back().split(".").front().append(".huf"));
                compressLZW(it, huffmanFileName);
            }
        }
    }
}

void Add_window::readAllBytesLZW(QString fileName, vector<char> &info)
{
    ifstream file(fileName.toLocal8Bit().constData(), ios::binary | ios::ate);
    if (file.is_open())
    {
        ifstream::pos_type pos = file.tellg();
        info.resize(pos);
        file.seekg(0, ios::beg);
        file.read(&info[0], pos);
    }
    else
    {
        qDebug()<<"ERROR1";
        QMessageBox msgBox(QMessageBox::Warning, "Error", "Unable to open file");
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        msgBox.exec();
    }
    file.close();
}

void Add_window:: writeCompressData(QString fileName, vector<int> &info)
{
    ofstream file(fileName.toLocal8Bit().constData(), ios::binary);
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

void Add_window::createTable(map<string, int> &table)
{
    for(int i = 0; i <= 255; i++)
    {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }
}

void Add_window::compressLZW(QString &compressFileName, QString &lzwFileName)
{
    map<string, int> table;
    vector<char> info;
    readAllBytesLZW(compressFileName, info);
    createTable(table);

    string p = "";
    string c = "";
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
    writeCompressData(lzwFileName, compressData);
}




void Add_window::decompressLZW(QString &lzwFileName, QString &decompressFileName)
{

}

void Add_window::compressHuffman(QString &compressFileName, QString &lzwFileName)
{

}
void Add_window::decompressHuffman(QString &lzwFileName, QString &decompressFileName)
{

}

