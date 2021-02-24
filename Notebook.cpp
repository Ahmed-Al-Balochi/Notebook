#include "Notebook.h"
#include "ui_Notebook.h"

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
   fontItalic();
}

void MainWindow::on_actionUnderline_triggered()
{
    fontUnderline();
}

void MainWindow::on_actionColor_triggered()
{
    textColor();
}


void MainWindow::on_actionBold_triggered()
{
    fontBold();
}

/*          #### Still Trying to make it work
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
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
   resizeImage();
}

void MainWindow::on_actionFont_Family_triggered()
{
     selectFont();
}

void MainWindow::on_actionStart_Painting_2_triggered()
{
    scribbleArea = new ScribbleArea;
   // scribbleArea->setParent(this);
    scribbleArea->setVisible(isVisible());
}

void MainWindow::on_actionEnd_Painting_triggered()
{
    const QByteArray fileFormat;
    // Define path, name and default file type
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    // Get selected file from dialog
    // Add the proper file formats and extensions
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));

    // If no file do nothing
    if (fileName.isEmpty()) {
        QMessageBox::warning(this,"Warning", "Cannot Save Image: ");
    } else {

        // Call for the file to be saved
        scribbleArea->saveImage(fileName, fileFormat.constData());
}
    //scribbleArea->setParent(this);
    //Textimage = scribbleArea->saveImage(currentFile, fileFormat.constData());
    Textimage = scribbleArea->image;
    getPaint(fileName);
    scribbleArea->setVisible(!isVisible());
}
