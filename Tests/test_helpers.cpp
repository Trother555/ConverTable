#include "test_helpers.h"

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
