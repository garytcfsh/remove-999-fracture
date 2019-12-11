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
    createPosTable();
    createElemTable();
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
    QStringList QSL_oneLine;
    QString oneLine;
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
    while(!oneLine.contains("FracElem"))
    {
        oneLine = streamIn.readLine();
        QSL_oneLine = oneLine.simplified().split(" ");
        if (QSL_oneLine[TYPE] == "4" && QSL_oneLine[HEAD].contains("999"))
            targetNode.append( QSL_oneLine[0]);
    }
    qDebug()<<"target list is created";
}

void MainWindow::createPosTable()
{
    QStringList QSL_oneLine;
    QString elemNum, oldFracNum, oldSetNum;
    int Frac, Set;
    streamIn.seek( fracElemPos);
    QSL_oneLine = fracElemLine.simplified().split(" ");
    for (int i=0; i<QSL_oneLine.count(); i++)
    {
        if (QSL_oneLine[i] == "Frac#")
            Frac = i;
        if (QSL_oneLine[i] == "Set#")
            Set = i;
    }
    while (elemNum != "0")
    {
        QSL_oneLine = streamIn.readLine().simplified().split(" ");
        elemNum = QSL_oneLine[0];
        if (oldFracNum != QSL_oneLine[Frac] || oldSetNum != QSL_oneLine[Set])
            if (elemNum != "0")
                pt.append( QSL_oneLine[Frac], QSL_oneLine[Set], QSL_oneLine[0].toInt());

        oldFracNum = QSL_oneLine[Frac];
        oldSetNum = QSL_oneLine[Set];
    }
    qDebug()<<"position table is created";
}

void MainWindow::createElemTable()
{
    //there is a strange property which is named "Minerals" in restart.mff
    et.createTable( fracElemLine.simplified().split(" ").count()-1);
    QString oneLine;
    streamIn.seek( fracElemPos);
    while (!oneLine.contains(" 0 "))
    {
        oneLine = streamIn.readLine();
        et.append( oneLine);
    }
    qDebug()<<"fracElem table is created";

}

void MainWindow::compareTargetNode()
{

}
