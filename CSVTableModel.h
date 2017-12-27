#ifndef CSVTABLE_H
#define CSVTABLE_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QByteArray>
#include <QAbstractTableModel>
#include <QtSql>

#include "elemettype.h"

enum ErrorCode
{
    NO_ERROR = 0,
    NO_SUCH_FILE = 1,
    UNEQUAL_COLUMN_COUNT = 2,
    HEADER_ERROR = 3,
    INSERT_ROW_ERROR = 4,
    SET_DATA_ERROR = 5
};

class CSVTableModel : public QSqlTableModel//QAbstractTableModel
{
    Q_OBJECT
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void reset();

    explicit CSVTableModel(QObject *parent = nullptr) : QSqlTableModel(parent){}//QAbstractTableModel(parent){}
    ErrorCode readFromFile(const QString& filename, const QString& sep);

signals:

public slots:

private:
    QList<QStringList> table;
    QStringList horizontalHeader;
    QVector<ElementType> columnTypes;

    void splitRow(const QByteArray &row, const QString& sep, QStringList& result, bool &isFullRow);
};











/**********************************************/
/*class CSVTable_old : public QObject
{
    Q_OBJECT
public:
    explicit CSVTable_old(QObject *parent) : QObject(parent){}
    ErrorCode read(const QString& filename, const QString& sep);

signals:

public slots:

private:
    QList<QStringList> table;
    QVector<ElementType> columnTypes;
    QStringList columnNames;
    QStringList splitRow(const QByteArray& row, const QString& sep);

    unsigned int rowCount, columnCount;
};*/
#endif // CSVTABLE_H
