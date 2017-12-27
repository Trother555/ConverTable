#include "DbTablesView.h"
#include <QTableView>
#include <QMouseEvent>
#include <QPainter>


DbTablesView::DbTablesView(QWidget*& p):QTabWidget(p)
{

}

void DbTablesView::SetModel(DbModel * dbModel)
{
    for(QSqlTableModel* tableModel : dbModel->getModels())
    {
	QTableView *tView = new QTableView();
	tView->setModel(tableModel);
	tView->setAlternatingRowColors(true);
	this->addTab(tView, tableModel->tableName());
    }
}

void DbTablesView::Clear()
{
    QWidget* w = nullptr;
    while((w = this->widget(0)))
    {
        delete w;
    }
    this->clear();
}
