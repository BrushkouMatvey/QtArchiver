#include "src/extract_window.h"
#include "ui_extract_window.h"
#include <QFileDialog>

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
    if(this->ui->LZW->isChecked())
        filesToDecompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to archive","D:\\","LZW files (*.lzw)");
    else
        filesToDecompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to archive","D:\\","HUF files (*.huf)");

    pathsForQLineEdit = filesToDecompress.join(";");
    this->ui->AppendLineEdit->setText(pathsForQLineEdit);
}
