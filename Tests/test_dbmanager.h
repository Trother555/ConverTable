#ifndef TEST_DBMANAGER_H
#define TEST_DBMANAGER_H
#include <QtTest>

class Test_DbManager : public QObject
{
    Q_OBJECT
private slots:
    void managerFetchesCorrectTables();
};

#endif // TEST_DBMANAGER_H
