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
    qDebug()<<table[0][0][ii];
    ii++;
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

int *ElemTable::searchFracSet(QString node)
{
    for (int i=1; i<4; i++)
    {
        for (int j=0; j<table[i]->count()-1; j++)
        {
            if ( node == table[i][j][0])
                ;
        }
    }
}
