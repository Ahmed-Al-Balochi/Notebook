#include "Notebook.h"
#include "ui_Notebook.h"
#include<QColorDialog>
#include<QByteArray>
#include<QInputDialog>

void MainWindow::FileStartup(){
QDate datetime = QDate::currentDate(); //works ok
ui->textEdit->setTextColor(myTextColor);
ui->textEdit->setText("Date: " + datetime.toString());
ui->textEdit->append("Subject: ");
}

void MainWindow::SaveFile(){
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toHtml();
    out<<text;
    file.close();
}

void MainWindow::NewFile(){
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::OpenFile(){

    QString filename = QFileDialog::getOpenFileName(this, "Open the File");
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

void MainWindow::PrintFile(){
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected){
     QMessageBox::warning(this, "Warning", "Cannot Access Printer");
     return;
    }
    ui->textEdit->print(&printer);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    // If they try to close maybeSave() returns true
    // if no changes have been made and the app closes
    if (maybeSave()) {
        event->accept();
    } else {

        // If there have been changes ignore the event
        event->ignore();
    }
}

    bool MainWindow::maybeSave(){
        // Check for changes since last save
        if (w->isModified()) {
           QMessageBox::StandardButton ret;

           // Scribble is the title
           // Add text and the buttons
           ret = QMessageBox::warning(this, tr("Scribble"),
                              tr("The File has been modified.\n"
                                 "Do you want to save your changes?"),
                              QMessageBox::Save | QMessageBox::Discard
                              | QMessageBox::Cancel);

           // If save button clicked call for file to be saved
            if (ret == QMessageBox::Save) {
                 SaveFile();

            // If cancel do nothing
            } else if (ret == QMessageBox::Cancel) {
                return false;
            }
        }
        return true;
    }

    void MainWindow::FilePath(){
        QString sPath = QDir::homePath();
        filemodel = new QFileSystemModel(this);
        filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs |QDir::Files); // make an option to backtrack
        filemodel->setRootPath(sPath);
        ui->treeView->setModel(filemodel);
        ui->treeView->setRootIndex(filemodel->index((sPath)));
    }
    void MainWindow::textColor()
    {
        // Store the chosen color from the dialog
        QColor newColor = QColorDialog::getColor(getTextColor());

        // If a valid color set it
        if (newColor.isValid())
            ui->textEdit->setTextColor(newColor);
    }

    void MainWindow::insertImage()
    {
        QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                      ".", tr("JPEG (*.jpg *jpeg)\n"
                                        "GIF (*.gif)\n"
                                        "Bitmap Files (*.bmp)\n"
                                        "PNG (*.png)\n"));
        QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
        image = QImageReader ( file ).read();

        QTextDocument * textDocument = ui->textEdit->document();
        textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextImageFormat imageFormat;
        imageFormat.setWidth( image.width() );
        imageFormat.setHeight( image.height() );
        imageFormat.setName( Uri.toString() );
        cursor.insertImage(imageFormat);
     }
