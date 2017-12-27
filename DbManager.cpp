#include "DbManager.h"

DbManager::DbManager(const QString& path, QString &&connectionName)
{
    conName = connectionName;
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",connectionName));
    m_db->setDatabaseName(path);
    if (!m_db->open())
    {
        qDebug() << "Error: connection with database fail";
        qDebug() << m_db->lastError();
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

}

QSqlTableModel* DbManager::getModel(const QString &tableName)
{
    QSqlTableModel* tmpModel = new QSqlTableModel(NULL, *m_db);
    tmpModel->setTable(tableName);
    tmpModel->select();
    models.push_back(tmpModel);
    return tmpModel;
}

QStringList DbManager::getTables()
{
    return m_db->tables(QSql::Tables);
}

DbManager::~DbManager()
{
    qDebug()<<"Deliting db manager and closing connection";
    for(auto&model:models)
    {
        delete model;
    }
    m_db->close();
    delete m_db;
    QSqlDatabase::removeDatabase(conName);
}
