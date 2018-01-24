#include "DbNamesListView.h"

DbNamesListView::DbNamesListView(QWidget* p):QListWidget(p)
{

}

void DbNamesListView::SetModel(AbstractTableModel * dbModel)
{
    for (QSqlTableModel* tableModel : dbModel->getModels())
    {
	QListWidgetItem *it = new QListWidgetItem();
	it->setText(tableModel->tableName());
	it->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
	it->setCheckState(Qt::Checked);
	this->addItem(it);

    }
}

void DbNamesListView::Clear()
{
    QListWidgetItem * w = nullptr;
    while ((w = this->item(0))!=nullptr)
	delete w;
    this->clear();
}

QStringList DbNamesListView::GetTablesToSave()
{
    QStringList tablesToSave;
    for (int i = 0;i<this->count();i++)
    {
        auto item = this->item(i);
        if (item->checkState() == Qt::Checked)
            tablesToSave.push_back(item->text());
    }
    return tablesToSave;
}

