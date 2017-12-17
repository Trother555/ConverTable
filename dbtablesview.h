#ifndef DBTABLESVIEW_H
#define DBTABLESVIEW_H
#include <QWidget>
#include <QTabWidget>
#include "DbManager.h"
#include <QtSql>

/**
 * @brief Представление для бд.
 *
 */
class DbTablesView : public QTabWidget
{
    Q_OBJECT
private:
    DbManager* m_dbm = NULL; /**< TODO: describe */
    QVector<QSqlTableModel*> models; /**< TODO: describe */
public:
    /**
     * @brief Конструктор для преобразования(promotion) исходного класса qt
     *
     * @param виджет-родитель
     */
    DbTablesView(QWidget*&);
    /**
     * @brief Устанавливает менеджер бд
     *
     * @param[in] Указатель на менеджер бд
     */
    void SetDbManager(DbManager*);
    /**
     * @brief Загружает таблицы из предоставленного DbManager
     *
     */
    void FetchTables();
    /**
     * @brief Очищает ресурсы, выделенные представлению
     *
     */
    void Clear();
    /**
     * @brief Сокращение для SetDbManager и FetchTables
     *
     * @param[in] Указатель на менеджер бд
     */
    void SetAndFetch(DbManager*);
    /**
     * @brief Возвращает модели таблтц в бд
     *
     * @return QVector<QSqlTableModel *>
     */
    QVector<QSqlTableModel*> getModels();

};

#endif // DBTABLESVIEW_H
