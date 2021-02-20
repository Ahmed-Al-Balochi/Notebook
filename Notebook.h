#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileSystemModel>
#include <QtGui>
#include <QDialog>
#include<QTreeView>
#include <QtCore>
#include<QWidget>
#include <QFileDialog>
#include <QTextStream>
#include<QTextEdit>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(const QString &fileName, QWidget *parent = nullptr);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isModified() const { return modified; }

protected:

   void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();


    void on_treeView_clicked(const QModelIndex &index);
    void on_actionAbout_triggered();

    void SaveFile();
    void NewFile();
    void OpenFile();
    void PrintFile();
    void FilePath();
    void FileStartup();


    void on_tabWidget_tabCloseRequested(int index);

    //void on_pushButton_clicked();

    void on_tabWidget_tabBarDoubleClicked(int index);

    void on_actionZoom_in_triggered();

    void on_actionZoom_Out_triggered();

private:
    Ui::MainWindow *ui;
    MainWindow *w;
    QString currentFile = "";

    QTextEdit *textFile;
    bool modified;
    bool maybeSave();
    int count = 0;

    QString fPath = "";
    QFileSystemModel *filemodel;
};
#endif // MAINWINDOW_H
