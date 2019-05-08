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

void Extract_window::on_pushButton_clicked()
{
    directory = QFileDialog::getExistingDirectory(this,
                               tr("Find Files"), QDir::currentPath());
    if (!directory.isEmpty())
    {
        ui->BrowseLineEdit->setText(directory);
    }
}
