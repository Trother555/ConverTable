#include "CsvManager.h"
#include <QString>


CsvManager::CsvManager(const QStringList &pathList)
{
    for(const QString& x : pathList)
    {
        CSVTableModel *tmpModel = new CSVTableModel();
        ErrorCode err = tmpModel->readFromFile(x, QString(","));

        if (err == ErrorCode::NO_ERROR)
        {
            QString csvName = x;
            csvName.chop(4);
            csvTables.insert(csvName, tmpModel);
        }
    }
}

QSqlTableModel *CsvManager::getModel(const QString &tableName)
{
    return csvTables[tableName];
}

QStringList CsvManager::getTables()
{
    return csvTables.keys();
}

CsvManager::~CsvManager()
{
    for (CSVTableModel* &x : csvTables.values())
    {
        delete x;
    }
    csvTables.clear();
}
