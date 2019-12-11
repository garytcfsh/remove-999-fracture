#include "postable.h"

posTable::posTable()
{

}

void posTable::append(QString fn, QString sn, int p)
{
    fracNum.append(fn);
    setNum.append(sn);
    pos.append(p);
}

int *posTable::searchPos(QString fn, QString sn)
{
    p = new int(2);
    p[0] = -1;
    p[1] = -1;
    // p[0] -> begin position of the fracture set
    // p[1] -> number of elem in the fracture set
    for (int i=0; i<fracNum.count(); i++)
    {
        //the last line is 0 0 x which doesn`t mach
        //so the largest i in this loop is fracNum.count()-2;
        if (fracNum[i] == fn && setNum[i] == sn)
        {
            p[0] = pos[i];
            p[1] = pos[i+1] - pos[i];

            updatePos( i, p[1]);
            i = fracNum.count();
        }
    }

    return p;
}

void posTable::updatePos(int i, int num)
{
    fracNum.removeAt(i);
    setNum.removeAt(i);
    pos.removeAt(i);
    for (int j=i; j<fracNum.count(); j++)
    {
        pos[i] = pos[i] - num;
    }
}
