#ifndef EXTRACT_WINDOW_H
#define EXTRACT_WINDOW_H

#include <QDialog>

namespace Ui {
class Extract_window;
}

class Extract_window : public QDialog
{
    Q_OBJECT

public:
    explicit Extract_window(QWidget *parent = nullptr);
    ~Extract_window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Extract_window *ui;
    QString directory;
};

#endif // EXTRACT_WINDOW_H
