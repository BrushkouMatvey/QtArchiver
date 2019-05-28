#include "src/extract_window.h"
#include "src/lzw.h"
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




