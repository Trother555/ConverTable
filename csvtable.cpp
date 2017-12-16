#include "csvtable.h"
#include <QFile>


QStringList CSVTable::splitRow(const QByteArray &row, const QString& sep)
{
    return ((QString)row).split(sep);
}


ErrorCode CSVTable::read(const QString &filename, const QString &sep)
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
        columnNames = splitRow(file.readLine(), sep);
        columnCount = columnNames.count();
        columnTypes.fill(ElementType::INT, columnCount);
    }


    while (!file.atEnd())
    {
        QStringList row = splitRow(file.readLine(), sep);

        if (columnCount != row.count())
        {
            file.close();
            return ErrorCode::UNEQUAL_COLUMN_COUNT;
        }

        for (int i = 0; i < row.count(); ++i)
        {
            ElementType type = getType(x);

            //Типы введены так:
            //INT = 0
            //DOUBLE = 1
            //STRING = 2
            //Если тип элемента столбца в текущей строке больше, чем тип предыдущих
            //элементов этого столбца, то нужно изменить тип всего столбца
            if (type > columnTypes[i])
            {
                columnTypes[i] = type;
            }
        }

        table.append(row);
        ++rowCount;
    }

    return ErrorCode::NO_ERROR;
}


