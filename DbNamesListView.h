#ifndef DBNAMESLISTVIEW_H
#define DBNAMESLISTVIEW_H
#include <QListWidget>
#include "DbManager.h"

class DbNamesListView : QListWidget
{
    Q_OBJECT
    QStringList tableNames;
public:
    DbNamesListView(QWidget*&);
    void SetDbManager(DbManager*);
    void FetchTables();
    void Clear();
    //То же что вызвать SetDbManager и затем FetchTables
    void SetAndFetch(DbManager*);
};

#endif // DBNAMESLISTVIEW_H
