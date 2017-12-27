#include "test_dbnameslistview.h"
#include "DbManager.h"
#include "DbNamesListView.h"
#include "test_helpers.h"
#include <QWidget>
#include "DbManager.h"

void Test_DbNamesListView::viewHasAllTablesPreSelected()
{
    QTemporaryDir tempDir;

    QString tempFile = createTempRes("mydatabase.sqlite", ":/database/Tests/mydatabase.sqlite", tempDir);
    QVERIFY2(tempFile != "", "Db failed to open");
    DbNamesListView dbView(NULL);
    DbModel dbm(new DbManager(tempFile));
    dbView.SetModel(&dbm);
    auto tts = dbView.GetTablesToSave();
    QVERIFY(tts.contains("Product"));
    QVERIFY(tts.contains("Warehouse"));
}
