#include "elemtable.h"

ElemTable::ElemTable()
{
    ii=0;
}

void ElemTable::countingSortNfsTable( int max)
{
    int min = 1;
    int size = max - min + 1;
    int *count = new int[size];
    for (int i=0; i<size; i++)
    {
        count[i] = count[i] + count[i-1];
    }
    QList< QStringList*> origin = nfsTable;
    for (int i=nfsTable.count()-1; i>=0; i--)
    {
        int n = origin[0][0][i].toInt();
        nfsTable[0][0][ --count[ n-min]] = origin[0][0][i];
        nfsTable[1][0][ --count[ n-min]] = origin[1][0][i];
        nfsTable[2][0][ --count[ n-min]] = origin[2][0][i];
    }
    qDebug()<<"df";
}

void ElemTable::appendNfs(QString n, QString f, QString s)
{
    nfsTable.append( new QStringList);
    nfsTable.last()->append(n);
    nfsTable.last()->append(f);
    nfsTable.last()->append(s);
}

void ElemTable::createTable( int n)
{
    for (int i=0; i<n; i++)
    {
        table.append( new QStringList);
        removedTable.append( new QStringList);
    }
}

void ElemTable::append(QString oneLine)
{
    QStringList QSL_oneLine = oneLine.simplified().split(" ");
    for (int i=0; i<table.count(); i++)
    {
        table[i]->append( QSL_oneLine[i]);
    }
    appendNfs( QSL_oneLine[1], QSL_oneLine[4], QSL_oneLine[5]);
    appendNfs( QSL_oneLine[2], QSL_oneLine[4], QSL_oneLine[5]);
    appendNfs( QSL_oneLine[3], QSL_oneLine[4], QSL_oneLine[5]);
    qDebug()<<table[0]->last();
}

void ElemTable::removeElem(int start, int num)
{
    for (int i=0; i<table.count(); i++)
    {
        for (int j=0; j<num; j++)
        {
            removedTable[i]->append( table[i][0][start]);
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
                qDebug()<<"frac"<<frac<<"set"<<set;
                qDebug()<<"i"<<i<<"j"<<j;
            }
        }
    }
    qDebug()<<a.elapsed()<<" ms";
}

void ElemTable::reNumberingElem()
{
    for (int i=0; i<table[0]->count()-1; i++)
    {
        table[0][0][i].setNum( i+1);
    }
    for (int i=0; i<removedTable[0]->count()-1; i++)
    {
        removedTable[0][0][i].setNum( i+1);
    }
    for (int i=0; i<table.count(); i++)
    {
        removedTable[i]->append( table[i]->last());
    }
}

QList< QStringList*> ElemTable::getTable()
{
    return table;
}

QList< QStringList*> ElemTable::getRemovedTable()
{
    return removedTable;
}
