#ifndef DbManager_H
#define DbManager_H

#include <QtSql>
#include <QObject>

/**
 * @brief Класс для работы с базой данных.
 * Содержит минимальный набор функций для работы с бд.
 *
 */
class DbManager : public QObject
{
    Q_OBJECT
    QString conName;
    QVector<QSqlTableModel*>models;
public:
    /**
     * @brief
     *
     * @param[in] path Путь к базе данных
     *
     * @param[in] connectionName Имя подключения к бд
     */
    DbManager(const QString& path, QString &&connectionName = "Default");

    /**
     * @brief Возвращает модель таблицы tableName, вызывая select() (см. QSqlTableModel::select())
     * Удалять указатели не надо, они будут удалены при удалении менеджера бд
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
    QSqlDatabase* m_db; /**< TODO: describe */
};

#endif // DbManager_H
