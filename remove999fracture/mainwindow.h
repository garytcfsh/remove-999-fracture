#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "postable.h"
#include "elemtable.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>
#include <QPlainTextEdit>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int openFile( QFile*, QString);
    void createFile( QFile*, QString);
    void createTargetNodeList();
    void createPosTable();
    void createElemTable();
    void compareTargetNode();
    void wrightFile();
    void createNewFile( QFile*, QString);
    void renameFile( QFile*, QFile*);

private slots:
    void on_selectFile_PB_clicked();

private:
    Ui::MainWindow *ui;
    QStringList targetNode;
    QTextStream streamIn, streamOut, streamOut2;
    qint64 headPos, nodePos, fracElemPos, gridElemPos;
    QString nodeLine, fracElemLine, gridElemLine;
    posTable pt;
    ElemTable et;
    QMessageBox msg;
    int maxNodeNum;
};
#endif // MAINWINDOW_H
