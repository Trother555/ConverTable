#ifndef DBNAMESLISTVIEW_H
#define DBNAMESLISTVIEW_H
#include <QListWidget>
#include "DbManager.h"
#include "dbmodel.h"

/**
 * @brief Представление для списка имён таблиц бд с возможностью выбора
 *
 */
class DbNamesListView : public QListWidget
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор для преобразования(promotion) исходного класса qt
     *
     * @param виджет-родитель
     */
    DbNamesListView(QWidget*);
    /**
      * @brief Устанавливает модель данных для представления.
      *
      * @param модель
      */
    void SetModel(DbModel * dbModel);
    /**
     * @brief Очищает ресурсы, выделенные представлению
     *
     */
    void Clear();
    /**
     * @brief Возвращает список имён таблиц, отмеченных в представлении
     *
     */
    QStringList GetTablesToSave();
};

#endif // DBNAMESLISTVIEW_H
