#include "DbTablesView.h"
#include <QTableView>
#include <QMouseEvent>
#include <QPainter>
#include <QHeaderView>


DbTablesView::DbTablesView(QWidget*& p):QTabWidget(p)
{

}

void DbTablesView::SetModel(AbstractTableModel * model)
{
    for (QSqlTableModel* tableModel : model->getModels())
    {
	QTableView *tView = new QTableView();
	tView->setModel(tableModel);
	tView->setAlternatingRowColors(true);
        tView->resizeRowsToContents();
	this->addTab(tView, tableModel->tableName());
    }
}

void DbTablesView::Clear()
{
    QWidget* w = nullptr;
    while ((w = this->widget(0)))
    {
        delete w;
    }
    this->clear();
}
