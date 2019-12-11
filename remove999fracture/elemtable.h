#ifndef ELEMTABLE_H
#define ELEMTABLE_H

#include "postable.h"
#include <QString>
#include <QList>
#include <QDebug>
#include <QMessageBox>

class ElemTable
{
public:
    ElemTable();

    void createTable( int);
    void append( QString);
    void removeElem( int, int);
    void searchFracSet( QString, posTable*);
    void reNumberingElem();
    QList< QStringList*> getTable();

private:
    QList< QStringList*> table;
    int ii;
    QString frac, set;
};

#endif // ELEMTABLE_H
