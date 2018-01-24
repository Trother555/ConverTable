#include "DbManager.h"
#include "test_dbmanager.h"
#include "test_dbnameslistview.h"
#include <QApplication>
#include "test_converter.h"



int main(int argc, char** argv)
{
   int status = 0;
   {
        Test_DbManager t;
        status |= QTest::qExec(&t, argc, argv);
   }
   {
        QApplication a(argc, argv);
        Test_DbNamesListView t;
        status |= QTest::qExec(&t, argc, argv);
   }
   {
       Test_Converter t;
       status |= QTest::qExec(&t, argc, argv);
   }
   return status;
}
