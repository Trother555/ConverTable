#ifndef ABSTRACTDBMODEL_H
#define ABSTRACTDBMODEL_H
#include <QtSql>

/**
 * @brief Интерфейс для модели базы данных
 *
 */
class AbstractTableModel
{
public:
    /**
     * @brief Возвращает модели таблиц
     *
     * @return const QVector<QSqlTableModel *> модели таблиц бд
     */
    virtual const QVector<QSqlTableModel*>& getModels() const = 0;

    /**
     * @brief Деструктор
     */
    virtual ~AbstractTableModel(){}
};

#endif // ABSTRACTDBMODEL_H
