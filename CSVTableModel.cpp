#include "CSVTableModel.h"
#include "CSVTableModel.h"
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




void CSVTableModel::splitRow(const QByteArray &row, const QString& sep, QStringList &result, bool& isFullRow)
{
    isFullRow = true;
    QString rowString(row);
    //Если строка в файле не последняя, то
    //сразу отрезается символ конца строки
    if (rowString.endsWith('\n'))
    {
        rowString.chop(1);
    }

    QStringList first = rowString.split(sep);

    int i=0;

    //Если передана неоконченная строка, то присоединить
    //её последнюю ячейку к первой ячейке текущей строки
    if (!result.isEmpty())
    {
        //Неполный последний элемент прошлой строки
        //становится частью первого элемента новой
        //
        //В середину вставляется символ конца строки,
        //удалённый в прошлом вызове функции
        first[0]=result.last()+"\n"+first[0];
        result.removeLast();

        //Если эта же строка заканчивается кавычкой
        if (first[0].endsWith('\"'))
        {
            result << first[0].remove(first[0].count()-1, 1).remove(0, 1);
            i=1;
        }
        //Если требуется поиск далее по списку
        else
        {
            int j=1;

            //Приклеиваем подстроки, пока не дойдём до конца
            //или пока не встретим закрывающую кавычку
            //
            //Добавляется сепаратор, т.к. он при сплите удалился
            while (j<first.count() && !first[j].endsWith('\"'))
            {
                first[0]+=sep+first[j];
                ++j;
            }


            //Если закончили из-за того, что перебрали все элементы строки,
            //то полученная строка была неполной и к ней надо добавить данные
            //из следующей строки файла
            if (j == first.count())
            {
                result << first[0];
                isFullRow = false;
                return;
            }

            //Нашли подстроку, заканчивающуюся кавычкой
            first[0]+=sep+first[j];
            result << first[0].remove(first[0].count()-1, 1).remove(0, 1);
            i=j+1;
        }
    }

    //rowString.ch//.remove(rowString.count()-1, 1).remove(0, 1);

    while (i<first.count())
    {
        //Если строка в списке, разделённом по sep, начинается с кавычки, то нужно найти
        //строку, заканчивающуюся кавычкой (возможно, это будет та же строка)
        if (first[i].startsWith('\"'))
        {
            //Если эта же строка заканчивается кавычкой
            if (first[i].endsWith('\"'))
            {
                result << first[i].remove(first[i].count()-1, 1).remove(0, 1);
                ++i;
            }
            //Если требуется поиск далее по списку
            else
            {
                int j=i+1;

                //Приклеиваем подстроки, пока не дойдём до конца
                //или пока не встретим закрывающую кавычку
                //
                //Добавляется сепаратор, т.к. он при сплите удалился
                while (j<first.count() && !first[j].endsWith('\"'))
                {
                    first[i]+=sep+first[j];
                    ++j;
                }

                //Если закончили из-за того, что перебрали все элементы строки,
                //то полученная строка была неполной и к ней надо добавить данные
                //из следующей строки файла
                if (j == first.count())
                {
                    result << first[i];
                    isFullRow = false;
                    return;
                }

                //Нашли подстроку, заканчивающуюся кавычкой
                //
                //Добавляется сепаратор, т.к. он при сплите удалился
                first[i]+=sep+first[j];
                result << first[i].remove(first[i].count()-1, 1).remove(0, 1);
                i=j+1;
            }
        }
        //Если строка начинается не с кавычки, то просто закидываем её в second
        else
        {
            result<<first[i];
            ++i;
        }
    }


    //return ((QString)row).split(sep);
}


ErrorCode CSVTableModel::readFromFile(const QString &filename, const QString &sep)
{
    if (this->rowCount() != 0)
    {
        reset();
    }

    if (!columnTypes.empty())
    {
        columnTypes.clear();
    }

    if (!horizontalHeader.empty())
    {
        horizontalHeader.clear();
    }

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ErrorCode::NO_SUCH_FILE;

    bool isFullRow = true;

    if (!file.atEnd())
    {
        splitRow(file.readLine(), sep, horizontalHeader, isFullRow);
        while (!isFullRow)
        {
            splitRow(file.readLine(), sep, horizontalHeader, isFullRow);
        }
        emit headerDataChanged(Qt::Orientation::Horizontal, 0, horizontalHeader.count()-1);
/*
        for (int i=0; i<horizontalHeader.count(); ++i)
        {
            if (!setHeaderData(i, Qt::Orientation::Horizontal, columnNames[i], Qt::EditRole))
            {
                return ErrorCode::HEADER_ERROR;
            }
        }
*/
        //columnCount = columnNames.count();
        columnTypes.fill(ElementType::INT, columnCount());
    }


    while (!file.atEnd())
    {
        QStringList row;

        splitRow(file.readLine(), sep, row, isFullRow);
        while (!isFullRow)
        {
            splitRow(file.readLine(), sep, row, isFullRow);
        }

        if (columnCount() != row.count())
        {
            file.close();
            return ErrorCode::UNEQUAL_COLUMN_COUNT;
        }

        for (int i = 0; i < row.count(); ++i)
        {
            ElementType type = getType(row[i]);

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

        //???
        emit beginInsertRows(QModelIndex(), table.count(), table.count());

        table.append(row);

        emit endInsertRows();

    }

    return ErrorCode::NO_ERROR;
}



/*QStringList CSVTable::splitRow(const QByteArray &row, const QString &sep)
{
    this->
}*/
