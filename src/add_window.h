#ifndef ADD_WINDOW_H
#define ADD_WINDOW_H

#include <QDialog>
#include "src/lzw.h"
#include "src/rle.h"
#include "src/huffman.h"

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
    void recvText(const QString &text);
private:
    Ui::Add_window *ui;
    QStringList filesToCompress;
    QString direct;
    QString pathsForQLineEdit;
    CompressorLZW compressorLzw;
    CompressorRLE compressorRle;
    CompressorHuffman compressorHuf;
};

#endif // ADD_WINDOW_H
