#ifndef ELEMTABLE_H
#define ELEMTABLE_H

#include "postable.h"
#include <QString>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>

class ElemTable
{
public:
    ElemTable();

    void createTable( int);
    void countingSortNfsTable();
    void removeRepeatNfsTable();
    int binarySearch( int, int, QString);
    void append( QString);
    void appendNfs( QString, QString, QString);
    void removeElem( int, int);
    void searchFracSet( QString, posTable*, QString);
    void reNumberingElem();
    QList< QStringList*> getTable();
    QList< QStringList*> getRemovedTable();

private:
    QList< QStringList*> table, removedTable, nfsTable;
    int ii;
    QString frac, set;
};

#endif // ELEMTABLE_H
