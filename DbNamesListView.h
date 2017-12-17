#ifndef DBNAMESLISTVIEW_H
#define DBNAMESLISTVIEW_H
#include <QListWidget>
#include "DbManager.h"

/**
 * @brief Представление для списка имён таблиц бд с возможностью выбора
 *
 */
class DbNamesListView : public QListWidget
{
    Q_OBJECT
    DbManager* m_dbm;
public:
    /**
     * @brief Конструктор для преобразования(promotion) исходного класса qt
     *
     * @param виджет-родитель
     */
    DbNamesListView(QWidget*);
    /**
     * @brief Установить внутренний менеджер бд
     *
     * @param[in] Указатель на менеджер бд
     */
    void SetDbManager(DbManager*);
    /**
     * @brief Загрузить информацию из бд в представление
     *
     */
    void FetchTables();
    /**
     * @brief Очистить представление
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
     * @brief Возвращает список имён таблиц, отмеченных в представлении
     *
     */
    QStringList GetTablesToSave();
};

#endif // DBNAMESLISTVIEW_H
