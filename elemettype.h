#ifndef ELEMETTYPE_H
#define ELEMETTYPE_H

#include <QString>

enum ElementType
{
    INT = 0,
    DOUBLE = 1,
    STRING = 2
};

ElementType getType(QString val);


#endif // ELEMETTYPE_H
