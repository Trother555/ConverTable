#include "DbManager.h"

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

}

QSqlTableModel* DbManager::getModel(const QString &tableName)
{
    QSqlTableModel* tmpModel = new QSqlTableModel(NULL, m_db);
    tmpModel->setTable(tableName);
    tmpModel->select();
    return tmpModel;
}

QStringList DbManager::getTables()
{
    return m_db.tables(QSql::Tables);
}
