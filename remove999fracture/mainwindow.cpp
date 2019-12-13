#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTime t;
    t.start();

    QFile fileIn, fileOut, fileOut2;
    QString fileType = "mff";

    if (openFile( &fileIn, fileType) == 0)
    {
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
        compareTargetNode();

        QString fileName = fileIn.fileName();
        fileName.remove( fileName.length()-3, 3);
        createNewFile( &fileOut2, fileName+"rm");
        fileName = fileName + "new";
        createNewFile( &fileOut, fileName);
        streamOut.setDevice( &fileOut);
        streamOut2.setDevice( &fileOut2);
        wrightFile();
        renameFile( &fileIn, &fileOut);
        fileIn.close();
        fileOut.close();
        fileOut2.close();

        msg.setText("The new restart file is created");
        msg.exec();
    }
    QString time;
    msg.setText(time.setNum(t.elapsed()));
    msg.exec();
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
    QString oneLine, lastNode, lastNode1, lastNode2;
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
        lastNode2 = lastNode1;
        lastNode1 = lastNode;
        lastNode = QSL_oneLine[0];
    }
    maxNodeNum = lastNode2.toInt();
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
    //the last line of data is 0  0  0  0
    //set the last line of posTable as 0 0 i
    int i=0;
    while (elemNum != "0")
    {
        QSL_oneLine = streamIn.readLine().simplified().split(" ");
        elemNum = QSL_oneLine[0];
        if (oldFracNum != QSL_oneLine[Frac] || oldSetNum != QSL_oneLine[Set])
            pt.append( QSL_oneLine[Frac], QSL_oneLine[Set], i);

        oldFracNum = QSL_oneLine[Frac];
        oldSetNum = QSL_oneLine[Set];
        i++;
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
    et.countingSortNfsTable();
    et.removeRepeatNfsTable();
    qDebug()<<"fracElem table is created";

}

void MainWindow::compareTargetNode()
{
    int err = 0;
    for (int i=0; i<targetNode.count(); i++)
    {
        err = et.searchFracSet( targetNode[i], &pt, "t");
        if (err == -1)
        {
            msg.setText("compare target node error: binary search error");
            msg.exec();
            i = targetNode.count();
        }
        else if (err == -2)
        {
            msg.setText("compare target node error: linear search error");
            msg.exec();
            i = targetNode.count();
        }
    }
    et.reNumberingElem();
    qDebug()<<"compare complete";
}

void MainWindow::createNewFile(QFile *newFile, QString fileName)
{
    newFile->setFileName( fileName);
    newFile->open( QFile::WriteOnly|QFile::Text);
}

void MainWindow::wrightFile()
{
    streamIn.seek(headPos);
    QString oneLine;

    while (!oneLine.contains("FracElem"))
    {
        oneLine = streamIn.readLine();
        streamOut << oneLine << endl;
        streamOut2 << oneLine << endl;
    }
    for (int i=0; i<et.getTable()[0]->count(); i++)
    {
        oneLine = "";
        for (int j=0; j<et.getTable().count(); j++)
        {
            oneLine = oneLine + '\t' + et.getTable()[j][0][i];
        }
        streamOut << oneLine << endl;
    }
    for (int i=0; i<et.getRemovedTable()[0]->count(); i++)
    {
        oneLine = "";
        for (int j=0; j<et.getRemovedTable().count(); j++)
        {
            oneLine = oneLine + '\t' + et.getRemovedTable()[j][0][i];
        }
        streamOut2 << oneLine << endl;
    }
    streamOut << gridElemLine << endl;
    streamOut2 << gridElemLine << endl;
    streamIn.seek(gridElemPos);
    while (!streamIn.atEnd())
    {
        oneLine = streamIn.readLine();
        streamOut << oneLine << endl;
        streamOut2 << oneLine << endl;
    }

}

void MainWindow::renameFile(QFile *oldFile, QFile *newFile)
{
    QString fileName = oldFile->fileName();
    fileName.remove( fileName.length()-3, 3);
    oldFile->rename( fileName + "old");
    newFile->rename( fileName + "mff");
}
