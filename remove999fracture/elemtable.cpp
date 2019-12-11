#include "elemtable.h"

ElemTable::ElemTable()
{
    ii=0;
    frac_set.append(" ");
    frac_set.append(" ");
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
    ii++;
    if (ii==5)
        table[0]->removeAt(3);
    qDebug()<<"df";
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

QStringList ElemTable::searchFracSet(QString node)
{
    for (int i=1; i<4; i++)
    {
        for (int j=0; j<table[i]->count()-1; j++)
        {
            if ( node == table[i][0][j])
            {
                nowX = i;
                nowY = j;
                frac_set[0] = table[4][0][j];
                frac_set[1] = table[5][0][j];

                return frac_set;
            }
        }
    }
}
