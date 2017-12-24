#ifndef TEST_DBNAMESLISTVIEW_H
#define TEST_DBNAMESLISTVIEW_H
#include <QtTest>

class Test_DbNamesListView : public QObject
{
    Q_OBJECT
private slots:
    void viewHasAllTablesPreSelected();
};

#endif // TEST_DBNAMESLISTVIEW_H
