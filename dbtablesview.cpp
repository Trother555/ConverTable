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
        tView->setModel(m_dbm->getModel(tableName));
        this->addTab(tView, tableName);
    }
}

void DbTablesView::ClearAllTabs()
{
    QWidget* w = nullptr;
    while(w = this->widget(0))
    {   delete ((QTableView*)w)->model();
        delete w;
    }

    if(m_dbm!=nullptr)
    {
        m_dbm->m_db.close();
        delete m_dbm;
    }
}

void DbTablesView::SetDbAndFetch(DbManager* dbManager)
{
    m_dbm = dbManager;
    this->FetchTables();
}

void DbTablesView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit click();
    }
}

void DbTablesView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(size().width()/2, size().height()/2, QPixmap(":/images/png/add-database.png").scaled(size()/4,Qt::KeepAspectRatio));
    QWidget::paintEvent(e);
}
