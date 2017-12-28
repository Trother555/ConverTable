#include "DbModel.h"

DbModel::DbModel(DbManager* db)
{
    db->setParent(this);
    QStringList tableNames = db->getTables();
    for(const auto& tableName : tableNames)
    {
        models.push_back(db->getModel(tableName));
    }
}

const QVector<QSqlTableModel*> DbModel::getModels()
{
    return models;
}

const QStringList DbModel::getTableNames()
{
    QStringList result;
    for(QSqlTableModel*m:models)
    {
        result.push_back(m->tableName());
    }
    return result;
}


DbModel::~DbModel()
{
    qDebug()<<"Deliting model";
}

