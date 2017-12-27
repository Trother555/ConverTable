#ifndef ABSTRACTMANAGER_H
#define ABSTRACTMANAGER_H

#include <QtSql>

class AbstractManager
{
public:
    virtual QSqlTableModel* getModel(const QString &tableName) = 0;
    virtual QStringList getTables() = 0;
    virtual ~AbstractManager(){}
};

#endif // ABSTRACTMANAGER_H
