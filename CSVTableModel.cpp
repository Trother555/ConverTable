#include "CSVTableModel.h"
#include <QFileInfo>
#include <QFile>
#include <QStringList>
#include <QString>





int CSVTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return table.count();
}

int CSVTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return horizontalHeader.count();
}

QVariant CSVTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.column() < 0 || index.column() >= columnCount()
        || index.row() < 0 || index.row() >= rowCount())
    {
        return QVariant();
    }

    return table.at(index.row()).at(index.column());
}

QVariant CSVTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    if (orientation == Qt::Vertical)
    {
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    if (section < 0 || section >= columnCount())
    {
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    return horizontalHeader.at(section);
}

void CSVTableModel::reset()
{
    emit beginRemoveRows(QModelIndex(), 0, table.count()-1);

    table.clear();
    horizontalHeader.clear();
    columnTypes.clear();

    emit endRemoveRows();
}




QStringList CSVTableModel::splitRow(const QString &row, const QString& sep, bool& isFull)
{
    QString rowCopy(row);
    isFull = true;

    int index = rowCopy.indexOf("\"\"");

    //Все парные двойные кавычки заменяются на спецсимвол 0x01
    while(index >= 0)
    {
       rowCopy[index] = 0x01; //заглушка для двойной кавычки
       rowCopy.remove(index+1, 1);

       index = rowCopy.indexOf("\"\"");
    }

    if (rowCopy.endsWith('\n'))
    {
        rowCopy.chop(1);
    }

    QStringList allParts = rowCopy.split(sep);
    QStringList result;

    int i=0;

    while(i<allParts.count())
    {
        if (allParts[i].startsWith('\"'))
        {
            if (allParts[i].endsWith('\"'))
            {
                allParts[i].remove(0, 1);
                allParts[i].chop(1);

                result << allParts[i];
                ++i;
            }
            else
            {
                int j=i+1;

                while(j<allParts.count() && !allParts[j].endsWith('\"'))
                {
                    allParts[i] += sep + allParts[j];
                    ++j;
                }


                //Если дошли до конца списка всех подстрок, но так и не нашли ту,
                //которая заканчивается на кавычку
                if (j==allParts.count())
                {
                    result << allParts[i];
                    isFull = false;

                    i = j; //условие выхода из внешнего while
                }
                //Если нашли строку, которая заканчивается на кавычку
                else
                {
                    allParts[i] += sep + allParts[j];
                    allParts[i].remove(0, 1);
                    allParts[i].chop(1); //удаляется кавычка

                    result << allParts[i];

                    i=j+1;
                }
            }
        }
        else
        {
            result << allParts[i];
            ++i;
        }
    }


    //Спецсимвол 0x01 во всех подстроках заменяется на кавычку
    for (int i=0; i<result.count(); ++i)
    {
        index = result[i].indexOf(0x01);
        while (index>=0)
        {
            result[i][index] = '\"';
            index = result[i].indexOf(0x01);
        }
    }


    if (!isFull && row.endsWith('\n'))
    {
        result.last() += '\n';
    }

    return result;
}


bool CSVTableModel::readFromFile(const QString &filename, const QString &sep)
{
    emit beginResetModel();

    if (rowCount() != 0)
    {
        reset();
    }

    if (!horizontalHeader.empty())
    {
        horizontalHeader.clear();
    }

    QFile csvFile(filename);

    if (!csvFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit endResetModel();
        return false;
    }

    setTable(QFileInfo(filename).completeBaseName());

    bool isFull=false;

    QStringList splittedRow = splitRow(csvFile.readLine(), sep, isFull);

    while (!csvFile.atEnd() && !isFull)
    {
        QString lastCell = splittedRow.last();
        splittedRow.removeLast();

        splittedRow.append(splitRow(lastCell + csvFile.readLine(), sep, isFull));
    }

    if (!isFull)
    {
        emit endResetModel();
        return false;
    }

    horizontalHeader = splittedRow;

    columnTypes.fill(ElementType::INTEGER, horizontalHeader.count());

    while (!csvFile.atEnd())
    {
        isFull=false;

        QStringList splittedRow = splitRow(csvFile.readLine(), sep, isFull);

        while (!csvFile.atEnd() && !isFull)
        {
            QString lastCell = splittedRow.last();
            splittedRow.removeLast();

            splittedRow.append(splitRow(lastCell + csvFile.readLine(), sep, isFull));
        }

        if (!isFull || splittedRow.count() != horizontalHeader.count())
        {
            horizontalHeader.clear();
            for (int i=0; i<table.count(); ++i)
            {
                table[i].clear();
            }
            table.clear();

            emit endResetModel();
            return false;
        }

        //строка сформирована

        for (int i=0; i<horizontalHeader.count(); ++i)
        {
            ElementType currentType = getType(splittedRow[i]);
            if (currentType > columnTypes[i])
            {
                columnTypes[i] = currentType;
            }
        }

        table.append(splittedRow);
    }

    emit endResetModel();

    return true;
}

const QVector<ElementType> &CSVTableModel::getColumnTypes() const
{
    return columnTypes;
}
