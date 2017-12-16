#include "elemettype.h"

ElementType getType(QString val)
{
    bool ok;

    val.toInt(&ok, 10);
    if (ok)
    {
        return ElementType::INT;
    }

    val.toDouble(&ok);
    if (ok)
    {
        return ElementType::DOUBLE;
    }

    return ElementType::STRING;
}
