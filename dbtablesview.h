#ifndef DBTABLESVIEW_H
#define DBTABLESVIEW_H
#include <QWidget>
#include <QTabWidget>
#include "dbmodel.h"
#include <QtSql>

/**
 * @brief Представление для бд
 *
 */
class DbTablesView : public QTabWidget
{
    Q_OBJECT
private:
public:
   /**
     * @brief Конструктор для преобразования(promotion) исходного класса qt
     *
     * @param виджет-родитель
     */
    DbTablesView(QWidget*&);
    /**
      * @brief Устанавливает модель данных для представления.
      *
      * @param модель
      */
    void SetModel(AbstractDbModel * dbModel);
    /**
     * @brief Очищает ресурсы, выделенные представлению
     *
     */
    void Clear();
};

#endif // DBTABLESVIEW_H
