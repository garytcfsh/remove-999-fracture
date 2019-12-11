#ifndef POSTABLE_H
#define POSTABLE_H

#include <QString>
#include <QList>

class posTable
{
public:
    posTable();

    void append( QString, QString, int);
    int *searchPos( QString, QString);
    void updatePos( int, int);

private:
    QStringList fracNum, setNum;
    QList< int> pos;
    int *p;
};


#endif // POSTABLE_H
