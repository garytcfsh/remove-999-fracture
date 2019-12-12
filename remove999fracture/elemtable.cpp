#include "elemtable.h"

ElemTable::ElemTable()
{
    ii=0;
}

void ElemTable::createTable( int n)
{
    for (int i=0; i<n; i++)
    {
        table.append( new QStringList);
    }
}

void ElemTable::append(QString oneLine)
{
    QStringList QSL_oneLine = oneLine.simplified().split(" ");
    for (int i=0; i<table.count(); i++)
    {
        table[i]->append( QSL_oneLine[i]);
    }
}

void ElemTable::removeElem(int start, int num)
{
    for (int i=0; i<table.count(); i++)
    {
        for (int j=0; j<num; j++)
        {
            table[i]->removeAt( start);
        }
    }
}

void ElemTable::searchFracSet(QString node, posTable *pt)
{
    QTime a;
    a.start();
    int *p;

    for (int i=1; i<4; i++)
    {
        for (int j=0; j<table[i]->count()-1; j++)
        {
            if ( node == table[i][0][j])
            {
                frac = table[4][0][j];
                set = table[5][0][j];

                p = pt->searchPos( frac, set);
                if (p[0] == -1)
                {
                    QMessageBox msg;
                    msg.setText("searchPos error");
                    msg.exec();
                }
                else
                {
                    removeElem( p[0], p[1]);
                    j = p[0];
                }
            }
        }
    }
    qDebug()<<a.elapsed();
    qDebug()<<table[0]->count();
    qDebug()<<"searchFracSet complete";
}

void ElemTable::reNumberingElem()
{
    for (int i=0; i<table[0]->count()-1; i++)
    {
        table[0][0][i].setNum( i+1);
    }
}

QList< QStringList*> ElemTable::getTable()
{
    return table;
}
