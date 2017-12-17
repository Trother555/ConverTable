#ifndef DbManager_H
#define DbManager_H

#include <QtSql>

/**
 * @brief Класс для работы с базой данных.
 * Содержит минимальный набор функций для работы с бд.
 *
 */
class DbManager
{

public:
    /**
     * @brief
     *
     * @param[in] path Путь к базе данных
     */
    DbManager(const QString& path);

    /**
     * @briefВозвращает модель таблицы tableName, вызывая select() (см. QSqlTableModel::select())
     *
     * @param tableName[in] Имя таблицы, для которой надо вернуть модель
     * @return QSqlTableModel Модель для использования в представлении DbTablesView
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
    ~DbManager();

//private:
    QSqlDatabase m_db; /**< TODO: describe */
};

#endif // DbManager_H
