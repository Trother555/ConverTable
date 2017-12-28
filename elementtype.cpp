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


QString getTypeString(ElementType type)
{
    switch (type)
    {
    case ElementType::INT:
        return QString("INTEGER");
    case ElementType::DOUBLE:
        return QString("REAL");
    case ElementType::STRING:
        return QString("TEXT");
    }
    return QString();
}
