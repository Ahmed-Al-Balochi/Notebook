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
#include<QImage>
#include <QPoint>
#include<QInputDialog>
#include<QPixmap>
#include<QLabel>
#include<QFontDialog>
#include<QFontComboBox>
#include<fakevim/fakevimhandler.h>
#include<resizeimage.h>
#include<paint.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ScribbleArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isModified() const { return modified; }
    QColor getTextColor() const { return myFontColor; }

protected:

   void closeEvent(QCloseEvent *event) override;

private slots:

   void SaveFile();
   void NewFile();
   void OpenFile();
   void PrintFile();
   void FilePath();
   void FileStartup();
   void textColor();

   void selectFont();
   void fontBold();
   void fontItalic();
   void fontUnderline();

   void insertImage();
   void resizeImage();

   void EndPainting();
   void getPaint(QString filepath);

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

    void on_actionZoom_in_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionItailc_triggered();

    void on_actionUnderline_triggered();

    void on_actionColor_triggered();

    void on_actionBold_triggered();

    void on_actionResize_Image_triggered();

    void on_actionFont_Family_triggered();

    void on_actionStart_Painting_triggered();

    void on_actionEnd_Painting_triggered();

    void on_actionInsertImage_triggered();

    /*void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_tabBarDoubleClicked(int index);

    void on_tabWidget_tabBarClicked(int index);

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();*/

private:
    Ui::MainWindow *ui;
    MainWindow *w;

    QString currentFile = "";
    QImage Textimage;
    QTextEdit *textFile;
    bool modified;

    QString fPath = "";
    QFileSystemModel *filemodel;

    QColor myFontColor = Qt::black;

    bool underline= false;
    bool italic = false;
    bool isbold = false;
    QFont q;

    ScribbleArea *scribbleArea;

    bool maybeSave();
};
#endif // MAINWINDOW_H
