#include "test_test.h"
#include "DbManager.h"
#include "test_dbmanager.h"
#include "test_dbnameslistview.h"
#include <QApplication>

void Test_Test::testTest()
{
    QVERIFY(true);
}


int main(int argc, char** argv)
{
   int status = 0;
   {
        Test_Test t;
        status |= QTest::qExec(&t, argc, argv);
   }
   {
        Test_DbManager t;
        status |= QTest::qExec(&t, argc, argv);
   }
   {
        QApplication a(argc, argv);
        Test_DbNamesListView t;
        status |= QTest::qExec(&t, argc, argv);
   }
   return status;
}
