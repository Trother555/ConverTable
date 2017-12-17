#ifndef DBTABLESVIEW_H
#define DBTABLESVIEW_H
#include <QWidget>
#include <QTabWidget>
#include "DbManager.h"
#include <QtSql>

class DbTablesView : public QTabWidget
{
    Q_OBJECT
private:
    DbManager* m_dbm = NULL;
    QVector<QSqlTableModel*> models;
public:
    DbTablesView(QWidget*&);
    //Устанавливает менеджер бд. Ссылку хранить не нужно. Будет удалён вызовом ClearAllTables.
    void SetDbManager(DbManager*);
    //Загружает таблицы из предоставленного DbManager
    void FetchTables();
    //Очищает ресурсы, выделенные представлению
    void Clear();
    //Сокращение для SetDbManager и FetchTables
    void SetAndFetch(DbManager*);
    QVector<QSqlTableModel*> getModels();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *e);

signals:
    void click();

};

#endif // DBTABLESVIEW_H
