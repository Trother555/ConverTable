#include "test_converter.h"
#include "SqlModelConverter.h"
#include "DbModel.h"
#include "CsvModel.h"

void test_converter::testConvertBothWaysSame()
{
    QTemporaryDir tempDir;

    QString tempFile = createTempRes("mydatabase.sqlite", ":/database/Tests/mydatabase.sqlite", tempDir);
    QVERIFY2(tempFile != "", "Db failed to open");
    DbModel dbm(new DbManager(tempFile));
    SqlModelConverter c(tempDir.path());
    QHash<QString,QString> resFile;
    c.sqlToCsv(dbm.getModels(),dbm.getTableNames(),resFile);

}
