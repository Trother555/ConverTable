#include "DbTablesView.h"
#include <QTableView>
#include <QMouseEvent>
#include <QPainter>

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
        QSqlTableModel *tmpModelPointer = m_dbm->getModel(tableName);
        models.append(tmpModelPointer);
        tView->setModel(tmpModelPointer);
        tView->setAlternatingRowColors(true);
        this->addTab(tView, tableName);
    }
}

void DbTablesView::Clear()
{
    models.clear();
    QWidget* w = nullptr;
    while((w = this->widget(0)))
    {
	QTableView* tView = qobject_cast<QTableView*>(w);
	if(tView!=nullptr)
	    delete tView->model();
        delete w;
    }
}

void DbTablesView::SetAndFetch(DbManager* dbManager)
{
    m_dbm = dbManager;
    this->FetchTables();
}

QVector<QSqlTableModel*> DbTablesView::getModels()
{
    return models;
}
