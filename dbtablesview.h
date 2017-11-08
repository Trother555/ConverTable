#ifndef DBTABLESVIEW_H
#define DBTABLESVIEW_H
#include <QWidget>
#include <QTabWidget>
#include "DbManager.h"
#include <QtSql>

class DbTablesView : public QTabWidget
{
    //Q_OBJECT
private:
    DbManager* m_dbm = NULL;
public:
    DbTablesView(QWidget*&);
    void SetDbManager(DbManager*);
    //Загружает таблицы из предоставленного DbManager
    void FetchTables();
    //УДАЛЯЕТ все вкладки, оставля TabWidget и
    //закрывает соединение менеджера баз данных
    void clearAllTabs();
};

#endif // DBTABLESVIEW_H
