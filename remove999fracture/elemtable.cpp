#include "elemtable.h"

ElemTable::ElemTable()
{
    ii=0;
}

void ElemTable::countingSortNfsTable()
{
    nfsTable.removeLast();
    nfsTable.removeLast();
    nfsTable.removeLast();
    int min = nfsTable[0][0][0].toInt(), max = 0;
    for (int i=nfsTable.count()-1; i>=0; --i)
    {
        int n = nfsTable[i][0][0].toInt();
        if ( max < n)
        {
            max = n;
        }
        if ( min > n)
        {
            min = n;
        }
    }
    int size = max - min + 1;
    int *count = new int[size];
    for (int i=0; i<size; i++)
        count[i] = 0;
    for (int i=0; i<nfsTable.count(); i++)
    {
        ++count[ nfsTable[i][0][0].toInt() - min];
    }
    for (int i=1; i<size; ++i)
    {
        count[i] += count[i-1];
    }
    QList< QStringList*> origin;
    for (int i=0; i<nfsTable.count(); i++)
    {
        origin.append( new QStringList);
        for (int j=0; j<3; j++)
        {
            origin[i]->append(nfsTable[i][0][j]);
        }
    }
    qDebug()<<"fd";
    for (int i=nfsTable.count()-1; i>=0; --i)
    {
        int n = origin[i][0][0].toInt();
        int nn = --count[ n-min];
        nfsTable[nn][0][0] = origin[i][0][0];
        nfsTable[nn][0][1] = origin[i][0][1];
        nfsTable[nn][0][2] = origin[i][0][2];
    }
    qDebug()<<"df";
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
}

void ElemTable::appendNfs(QString n, QString f, QString s)
{
    nfsTable.append( new QStringList);
    nfsTable.last()->append(n);
    nfsTable.last()->append(f);
    nfsTable.last()->append(s);
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
