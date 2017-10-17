#ifndef DbManager_H
#define DbManager_H

#include <QtSql>

class DbManager
{

public:
    DbManager(const QString& path);

    //Возвращает модель таблицы tableName, вызывая select()
    QSqlTableModel* getModel(QString &tableName);

    QStringList getTables();

//private:
    QSqlDatabase m_db;
};

#endif // DbManager_H
