#ifndef DBMODEL_H
#define DBMODEL_H
#include "DbManager.h"
#include <QtSql>
#include "AbstractDbModel.h"
/**
 * @brief Модель базы данных
 *
 */
class DbModel : QObject, public AbstractTableModel
{
    Q_OBJECT
    QVector<QSqlTableModel*> models;
public:
    /**
     * @brief
     *
     * @param db Менеджер бд. Будет удалён автоматически при удалении Model.
     */
    DbModel(DbManager* db);
    const QVector<QSqlTableModel*>& getModels() const override;
    QStringList getTableNames() const;
    ~DbModel();
};

#endif // DBMODEL_H
