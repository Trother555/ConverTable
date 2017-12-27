#ifndef ABSTRACTDBMODEL_H
#define ABSTRACTDBMODEL_H
#include <QtSql>

class AbstractDbModel
{
public:
    virtual const QVector<QSqlTableModel*> getModels() = 0;
};

#endif // ABSTRACTDBMODEL_H
