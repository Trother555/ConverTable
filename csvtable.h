#ifndef CSVTABLE_H
#define CSVTABLE_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QByteArray>

#include "elemettype.h"

enum ErrorCode
{
    NO_ERROR = 0,
    NO_SUCH_FILE = 1,
    UNEQUAL_COLUMN_COUNT = 2
};

class CSVTable : public QObject
{
    Q_OBJECT
public:
    explicit CSVTable(QObject *parent) : QObject(parent){}
    ErrorCode read(const QString& filename, const QString& sep);

signals:

public slots:

private:
    QList<QStringList> table;
    QVector<ElementType> columnTypes;
    QStringList columnNames;
    QStringList splitRow(const QByteArray& row, const QString& sep);

    unsigned int rowCount, columnCount;
};

#endif // CSVTABLE_H
