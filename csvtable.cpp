#include "csvtable.h"
#include <QFile>


ErrorCode CSVTable::read(QString filename, QString sep)
{
    if (!table.empty())
    {
        for(QStringList& row : table)
        {
            row.clear();
        }

        table.clear();
    }

    if (!columnTypes.empty())
    {
        columnTypes.clear();
    }

    columnCount = rowCount = 0;

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ErrorCode::NO_SUCH_FILE;

    if (!file.atEnd())
    {
        QStringList row = splitRow(file.readLine());
        columnCount = row.count();

        table.append(row);
        ++rowCount;
    }


    while (!file.atEnd())
    {

    }

};
