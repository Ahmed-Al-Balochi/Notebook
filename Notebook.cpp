#include "Notebook.h"
#include "ui_Notebook.h"
//#include "Functions.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->textEdit);
    path();
    QDate datetime = QDate::currentDate(); //works ok
    ui->textEdit->setText("Date: " + datetime.toString());
    ui->textEdit->append("Subject: ");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    NewFile();
}

void MainWindow::on_actionOpen_triggered()
{
    OpenFile();
}

void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionPrint_triggered()
{
    Print();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}



void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}



void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if(filemodel->fileInfo(index).isFile()){
    fPath = filemodel->fileInfo(index).absoluteFilePath();
    QString filename = fPath;
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About Notebook"," Thank You for Using my Notebook App!\n Author: Ahmed Al Balochi\n Student of Computer Science at Riphah International University"
                                       "\n Email: a7mad98.work@gmail.com\n Github Page Link: https://github.com/Ahmed-Al-Balochi");
}

