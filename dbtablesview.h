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
public:
    DbTablesView(QWidget*&);
    void SetDbManager(DbManager*);
    //Загружает таблицы из предоставленного DbManager
    void FetchTables();
    //УДАЛЯЕТ все вкладки, оставля TabWidget и
    //закрывает соединение менеджера баз данных
    void ClearAllTabs();
    //То же что вызвать SetDbManager и затем FetchTables
    void SetDbAndFetch(DbManager*);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void click();

};

#endif // DBTABLESVIEW_H
