#ifndef ADD_WINDOW_H
#define ADD_WINDOW_H

#include <QDialog>

namespace Ui {
class Add_window;
}

class Add_window : public QDialog
{
    Q_OBJECT

public:
    explicit Add_window(QWidget *parent = nullptr);
    ~Add_window();

private slots:
    void on_BrowseButton_clicked();

    void on_AppendButton_clicked();

    void on_Ok_clicked();
private:
    Ui::Add_window *ui;
    QStringList filesToCompress;
    QString direct;
    QString pathsForQLineEdit;
    QStringList fileNames;

private:
    void readAllBytesLZW(QString fileName, std::vector<char> &info);
    void writeCompressDataLZW(QString fileName, std::vector<int> &info);
    void createTableLZW(std::map <std::string, int> &table);

    void compressLZW(QString &compressFileName, QString &lzwFileName);

    void compressHuffman(QString &compressFileName, QString &lzwFileName);

    void readAllBytesFromLzwFile(QString fileName, std::vector<int> &info);

};

#endif // ADD_WINDOW_H
