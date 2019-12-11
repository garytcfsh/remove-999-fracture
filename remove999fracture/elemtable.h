#ifndef ELEMTABLE_H
#define ELEMTABLE_H

#include <QString>
#include <QList>
#include <QDebug>

class ElemTable
{
public:
    ElemTable();

    void createTable( int);
    void append( QString);
    void removeElem( int, int);
    QStringList searchFracSet( QString);

private:
    QList< QStringList*> table;
    int ii;
    QStringList frac_set;
    int nowX, nowY;
};

#endif // ELEMTABLE_H
