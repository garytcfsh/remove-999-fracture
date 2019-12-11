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

private:
    QList< QStringList*> table;
};

#endif // ELEMTABLE_H
