#include "CSVModel.h"
#include "CSVTableModel.h"


CSVModel::CSVModel(const QStringList &names)
{
    for (auto& x : names)
    {
        CSVTableModel* tmpModel = new CSVTableModel();
        if (tmpModel->readFromFile(x, ","))
            models.push_back(tmpModel);
        else
            delete tmpModel;
    }
}

const QVector<QSqlTableModel*>& CSVModel::getModels() const
{
    return models;
}
