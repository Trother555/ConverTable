#include "DbTablesView.h"
#include <QTableView>

DbTablesView::DbTablesView(QWidget*& p):QTabWidget(p)
{

}

void DbTablesView::SetDbManager(DbManager * dbManager)
{
    m_dbm = dbManager;
}

void DbTablesView::FetchTables()
{
    QStringList tableNames = m_dbm->getTables();
    for(const auto &tableName : tableName)
    {
        QTableView *tView = new QTableView();
        tView->setModel(m_dbm->getModel(tableName));
        this->addTab(tView, tableName);
    }
}

void DbTablesView::clearAllTabs()
{

}
