#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
 #include <QFileSystemModel>
#include <QtGui>
#include <QDialog>
#include <QtCore>
#include <QFileDialog>
#include <QTextStream>
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

    void save();
    void NewFile();
    void OpenFile();
    void Print();

private:
    Ui::MainWindow *ui;
    MainWindow *w;
    QString currentFile = "";

    bool modified;

    QString fPath = "";
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;

    bool maybeSave();
};
#endif // MAINWINDOW_H
