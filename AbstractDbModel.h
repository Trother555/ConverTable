#ifndef ABSTRACTDBMODEL_H
#define ABSTRACTDBMODEL_H
#include <QtSql>

/**
 * @brief Интерфейс для модели базы данных
 *
 */
class AbstractDbModel
{
public:
    /**
     * @brief Возвращает модели таблиц
     *
     * @return const QVector<QSqlTableModel *> модели таблиц бд
     */
    virtual const QVector<QSqlTableModel*> getModels() = 0;
    virtual ~AbstractDbModel(){}
};

#endif // ABSTRACTDBMODEL_H
