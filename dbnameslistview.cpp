#include "DbNamesListView.h"

DbNamesListView::DbNamesListView(QWidget* p):QListWidget(p)
{

}

void DbNamesListView::SetDbManager(DbManager * dbManager)
{
    m_dbm = dbManager;
}

void DbNamesListView::FetchTables()
{
    //Set db list in settings
    for(auto name:m_dbm->getTables())
    {
	QListWidgetItem *it = new QListWidgetItem();
	it->setText(name);
	it->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
	it->setCheckState(Qt::Checked);
	this->addItem(it);
    }
}

void DbNamesListView::SetAndFetch(DbManager * dbManager)
{
    SetDbManager(dbManager);
    FetchTables();
}

void DbNamesListView::Clear()
{
    QListWidgetItem *ptr;
    while((ptr = this->item(0))!=nullptr)
	delete ptr;
}

QStringList DbNamesListView::GetTablesToSave()
{
    QStringList tablesToSave;
    for(int i = 0;i<this->count();i++)
    {
	auto item = this->item(i);
	if(item->checkState() == Qt::Checked)
	    tablesToSave.push_back(item->text());
    }
    return tablesToSave;
}

