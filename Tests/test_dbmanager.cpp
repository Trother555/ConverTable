#include "test_dbmanager.h"
#include "DbManager.h"

QString createTempRes(QString fileName, QString resURL, QTemporaryDir &tempDir)
{
    if (tempDir.isValid())
    {
      const QString tempFile = tempDir.path() + "/" + fileName;
      if (QFile::copy(resURL, tempFile)) {
          return tempFile;
      }
    }
    return "";
}

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
