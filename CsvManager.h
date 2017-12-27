#ifndef CsvManager_H
#define CsvManager_H

#include <QtSql>
#include <CSVTableModel.h>
#include "AbstractManager.h"

/**
 * @brief Класс для работы с базой данных.
 * Содержит минимальный набор функций для работы с бд.
 *
 */
class CsvManager: public AbstractManager
{

public:
    /**
     * @brief
     *
     * @param[in] pathList Список путей к csv-файлам
     */
    CsvManager(const QStringList& pathList);

    /**
     * @brief Возвращает модель таблицы tableName, вызывая select() (см. QSqlTableModel::select())
     *
     * @param tableName[in] Имя таблицы, для которой надо вернуть модель
     * @return QSqlTableModel Модель для использования в представлении CsvTablesView
     */
    QSqlTableModel* getModel(const QString &tableName);

    /**
     * @brief Возвращает таблицы
     *
     * @return QStringList
     */
    QStringList getTables();
    /**
     * @brief Возвращает список с именами таблиц.
     *
     */
    ~CsvManager();

//private:
    QMap<QString, CSVTableModel*> csvTables; /**< TODO: describe */
};

#endif // CsvManager_H
