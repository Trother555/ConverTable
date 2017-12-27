#include "DbModel.h"

DbModel::DbModel(DbManager* db)
{
    db->setParent(this);
    QStringList tableNames = db->getTables();
    for(const auto& tableName : tableNames)
    {
	models.append(db->getModel(tableName));
    }
}

const QVector<QSqlTableModel*> DbModel::getModels()
{
    return models;
}

DbModel::~DbModel()
{
    qDebug()<<"Deliting model";
}

