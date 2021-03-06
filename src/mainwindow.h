#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>

#include "src/add_window.h"
#include "src/extract_window.h"

#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum Page
    {
        ADD_WINDOW,
        EXTRACT_WINDOW
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void synchronizeListFromEdit();
    void createFileSystemModel();
    void setQLineEditToToolBar();
    ~MainWindow();
signals:
    void emitText(const QString &text);
private slots:
    void on_actionAdd_files_to_archive_triggered();
    void on_actionExtract_to_triggered();

    void on_listView_clicked(const QModelIndex &index);
    void on_listView_doubleClicked(const QModelIndex &index);
    void EnterPressed();
    void upOnLevel();
    void on_actionDelete_file_triggered();

private:
    Ui::MainWindow *ui;
    QMap<int, QDialog*> m_mapPages;
    void init();
    QFileSystemModel *model;
    QLineEdit *toolBarLineEdit;
    QWidget *spacer;
    QString toolBarTextBeforeChanged;
};

#endif // MAINWINDOW_H
