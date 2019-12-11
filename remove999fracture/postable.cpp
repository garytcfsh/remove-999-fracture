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
    // p[0] -> begin position of the fracture set
    // p[1] -> number of elem in the fracture set
    // if p[1] is zero, means that it is the lastest fracture set
    for (int i=0; i<fracNum.count(); i++)
    {
        if (fracNum[i] == fn && setNum[i] == sn)
        {
            p[0] = pos[i];
            if (i == fracNum.count()-1)
                p[1] = 0;
            else
                p[1] = pos[i+1] - pos[i];
        }
    }

    return p;
}
