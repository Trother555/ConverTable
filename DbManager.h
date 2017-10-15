#ifndef DbManager_H
#define DbManager_H

#include <QtSql>

class DbManager
{

public:
    DbManager(const QString& path);

    QSqlTableModel* getModel();

private:
    QSqlDatabase m_db;
};

#endif // DbManager_H
