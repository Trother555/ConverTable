#ifndef CSVMODEL_H
#define CSVMODEL_H

#include "AbstractDbModel.h"

class CsvModel : QObject, public AbstractDbModel
{
    Q_OBJECT
    QVector<QSqlTableModel*> models;
public:
    /**
     * @brief
     *
     * @param db Менеджер бд. Будет удалён автоматически при удалении Model.
     */
    CsvModel(const QStringList& names);
    const QVector<QSqlTableModel*> getModels();
    ~CsvModel(){}
};

#endif // CSVMODEL_H
