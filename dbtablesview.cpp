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
    for(const auto& tableName : tableNames)
    {
        QTableView *tView = new QTableView();
        tView->setModel(m_dbm->getModel(tableName));
        this->addTab(tView, tableName);
    }
}

void DbTablesView::clearAllTabs()
{
    QWidget* w = nullptr;
    while(w = this->widget(0))
    {   delete ((QTableView*)w)->model();
        delete w;
    }
}

void DbTablesView::closeDb()
{
    if(m_dbm!=nullptr)
    {
        m_dbm->m_db.close();
        delete m_dbm;
    }
}
