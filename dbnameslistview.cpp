#include "DbNamesListView.h"

DbNamesListView::DbNamesListView(QWidget*& p):QListWidget(p)
{

}

void DbNamesListView::SetDbManager(DbManager * dbManager)
{
    m_dbm = dbManager;
}

void DbNamesListView::FetchTables()
{
    tableNames = m_dbm->getTables();
}
