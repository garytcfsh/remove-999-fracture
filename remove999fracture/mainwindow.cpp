#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile fileIn;
    QString fileType = "mff";

    openFile( &fileIn, fileType);
    streamIn.setDevice( &fileIn);

    QString oneLine;
    headPos = streamIn.pos();
    while (!streamIn.atEnd())
    {
        oneLine = streamIn.readLine();
        if (oneLine.contains(" NODE "))
        {
            nodePos = streamIn.pos();
            nodeLine = oneLine;
        }
        if (oneLine.contains("FracElem"))
        {
            fracElemPos = streamIn.pos();
            fracElemLine = oneLine;
        }
        if (oneLine.contains("ELEM"))
        {
            gridElemPos = streamIn.pos();
            gridElemLine = oneLine;
        }
    }
    createTargetNodeList();
}

MainWindow::~MainWindow()
{
    delete ui;

}

int MainWindow::openFile(QFile *file, QString fileType)
{
    QString filePath = QFileDialog::getOpenFileName(
                this,
                tr("Select a file"),
                "",
                fileType + " Files (*." + fileType + ")");
    if (!filePath.isNull())
    {
        file->setFileName( filePath);
        file->open( QFile::ReadOnly|QFile::Text);

        return 0;
    }
    return -1;
}

void MainWindow::createFile(QFile *file, QString fileName)
{
    file->setFileName( fileName);
    file->open( QFile::WriteOnly|QFile::Text);
}

void MainWindow::createTargetNodeList()
{
    qDebug()<<"c";
    QStringList QSL_oneLine;
    int TYPE, HEAD;
    streamIn.seek( nodePos);
    QSL_oneLine = nodeLine.simplified().split(" ");
    for (int i=0; i<QSL_oneLine.count(); i++)
    {
        if (QSL_oneLine[i] == "TYPE")
            TYPE = i;
        if (QSL_oneLine[i] == "HEAD")
            HEAD = i;
    }
    qDebug()<<QSL_oneLine;
    qDebug()<<TYPE<<HEAD;
    while(streamIn.pos() != fracElemPos)
    {
        QSL_oneLine = streamIn.readLine().simplified().split(" ");
        if (QSL_oneLine[TYPE] == "4" && QSL_oneLine[HEAD].contains("999"))
            targetNode.append( QSL_oneLine[0]);
    }


}
