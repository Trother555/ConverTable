#include "test_dbmanager.h"
#include "DbManager.h"
#include "test_helpers.h"

void Test_DbManager::managerFetchesCorrectTables()
{
    QTemporaryDir tempDir;

    QString tempFile = createTempRes("mydatabase.sqlite", ":/database/Tests/mydatabase.sqlite", tempDir);
    QVERIFY2(tempFile != "", "Db failed to open");
    DbManager dbm(tempFile);
    auto tableNames = dbm.getTables();
    QVERIFY(tableNames.contains("Product"));
    QVERIFY(tableNames.contains("Warehouse"));

}

//QTEST_MAIN(Test_DbManager)
