#include "Notebook.h"
#include "ui_Notebook.h"
#include<resizeimage.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->textEdit);     ui->textEdit->setParent(ui->tab);

    FilePath();
    FileStartup();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    maybeSave();
    NewFile();
}

void MainWindow::on_actionOpen_triggered()
{
    OpenFile();
}

void MainWindow::on_actionSave_triggered()
{
    SaveFile();
}

void MainWindow::on_actionPrint_triggered()
{
    PrintFile();
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


void MainWindow::on_actionZoom_in_triggered()
{
    ui->textEdit->zoomIn(5);
}

void MainWindow::on_actionZoom_Out_triggered()
{
    ui->textEdit->zoomOut(5);
}


void MainWindow::on_actionItailc_triggered()
{
    if(!italic){
        italic = true;
        ui->textEdit->setFontItalic(italic);
    }
    else{
         italic = false;
        ui->textEdit->setFontItalic(italic);
    }
}

void MainWindow::on_actionUnderline_triggered()
{
    if(!underline){
        underline = true;
        ui->textEdit->setFontUnderline(underline);
    }
    else{
         underline = false;
        ui->textEdit->setFontUnderline(underline);
    }
}

void MainWindow::on_actionColor_triggered()
{
    textColor();
}

/*          #### Still Trying to make it work
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionBold_triggered()
{
    ui->textEdit->underMouse();
    if(!isbold){
        isbold= true;
        q.setBold(isbold);
        ui->textEdit->setFont(q);
    }
    else{
        isbold= false;
        q.setBold(isbold);
        ui->textEdit->setFont(q);
    }
}


void MainWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
    ui->tabWidget->insertTab(index,(new MainWindow())->ui->tab,QString("index %1").arg(ui->tabWidget->currentIndex()));
    //QMessageBox::warning(this,"Warning", &"Cannot open file: " [ ui->tabWidget->currentIndex()]);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    //QMessageBox::warning(this,"Warning", &"Cannot open file: " [ ui->tabWidget->currentIndex()]);
}

void MainWindow::on_pushButton_clicked()
{
     ui->tabWidget->addTab((new MainWindow())->ui->tab,QString("index %1").arg(ui->tabWidget->currentIndex()));
}
*/


void MainWindow::on_actionStart_Painting_triggered()
{
        insertImage();
}

void MainWindow::on_actionResize_Image_triggered(){
    QTextBlock currentBlock = ui->textEdit->textCursor().block();
        QTextBlock::iterator it;

        for (it = currentBlock.begin(); !(it.atEnd()); ++it)
        {

                 QTextFragment fragment = it.fragment();



                 if (fragment.isValid())
                 {

                     if(fragment.charFormat().isImageFormat ())
                     {
                          QTextImageFormat newImageFormat = fragment.charFormat().toImageFormat();

                          QPair<double, double> size = ResizeImageDialog::getNewSize(this, newImageFormat.width(), newImageFormat.height());

                          newImageFormat.setWidth(size.first);
                          newImageFormat.setHeight(size.second);

                          if (newImageFormat.isValid())
                          {
                              //QMessageBox::about(this, "Fragment", fragment.text());
                              //newImageFormat.setName(":/icons/text_bold.png");
                              QTextCursor helper = ui->textEdit->textCursor();

                              helper.setPosition(fragment.position());
                              helper.setPosition(fragment.position() + fragment.length(),
                                                  QTextCursor::KeepAnchor);
                              helper.setCharFormat(newImageFormat);
                          }
                      }
                  }
           }
}
