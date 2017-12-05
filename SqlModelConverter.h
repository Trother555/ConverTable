#ifndef SQLMODELCONVERTER_H
#define SQLMODELCONVERTER_H

#include <QString>
#include <QtSql>

class SqlModelConverter
{
private:
    const QString m_delim;
    const QString m_endOfLine;
    const bool m_getFieldNames;

public:
    SqlModelConverter(QString delim = ",",
                      QString endOfLine = "\n",
                      bool getFieldNames = false):
        m_delim(delim),m_endOfLine(endOfLine),m_getFieldNames(getFieldNames)
    {}

    void sqlToCsv(QVector<QSqlTableModel*> models, QHash<QString, QString>& result);
};

#endif // SQLMODELCONVERTER_H
