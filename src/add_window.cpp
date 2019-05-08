#include "src/add_window.h"
#include "ui_add_window.h"
#include <QFileDialog>
#include <QDebug>
#define SPACE ' '

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

}

void Add_window::on_AppendButton_clicked()
{
    filesToAdd = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to archive", "");
    paths = filesToAdd.join(";");
    this->ui->BrowseLineEdit->setText(paths);
}
