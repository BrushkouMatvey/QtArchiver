#include "src/add_window.h"
#include "ui_add_window.h"
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
    filesToCompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to archive","D:\\","Text Files (*.txt *.cpp *.docx *.rtf)");

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
        if (!dir.exists())
        {
          dir.mkdir(".");
        }

        if(this->ui->LZWRadioButton->isChecked())
        {
            for(auto it:filesToCompress)
            {
                QString tempDir = direct;
                QString lzwFileName = tempDir.append(it.split("/").back().split(".").front().append(".lzw").prepend("/"));
                compressorLzw.compressLZW(it, lzwFileName);
            }
        }
        else if(this->ui->RLERadioButton->isChecked())
        {
            for(auto it:filesToCompress)
            {
                QString tempDir = direct;
                QString rleFileName =  tempDir.append(it.split("/").back().split(".").front().append(".rle").prepend("/"));
                compressorRle.compressRLE(it, rleFileName);
            }
        }
        else
        {
            for(auto it:filesToCompress)
            {
                QString tempDir = direct;
                QString huffmanFileName =  tempDir.append(it.split("/").back().split(".").front().append(".huf").prepend("/"));
                compressorHuf.compressHuffman(it, huffmanFileName);
            }
        }
    }
}




