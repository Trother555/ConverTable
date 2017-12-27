#include "DbNamesListView.h"

DbNamesListView::DbNamesListView(QWidget* p):QListWidget(p)
{

}

void DbNamesListView::SetDbManager(AbstractManager *dbManager)
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

void DbNamesListView::SetAndFetch(AbstractManager * dbManager)
{
    SetDbManager(dbManager);
    FetchTables();
}

void DbNamesListView::Clear()
{
    this->clear();
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

