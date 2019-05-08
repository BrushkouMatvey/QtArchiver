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

private:
    Ui::Add_window *ui;
    QStringList filesToAdd;
    QString paths;
};

#endif // ADD_WINDOW_H
