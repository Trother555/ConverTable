#include "CsvModel.h"
#include "CSVTableModel.h"


CsvModel::CsvModel(const QStringList &names)
{
    for (auto& x : names)
    {
        CSVTableModel* tmpModel = new CSVTableModel();
        tmpModel->readFromFile(x, ",");
        models.push_back(tmpModel);
    }
}

const QVector<QSqlTableModel *> CsvModel::getModels()
{
    return models;
}
