#ifndef SQLMODELCONVERTER_H
#define SQLMODELCONVERTER_H

#include <QString>
#include <QtSql>

class ConverterOptions
{
    friend class SqlModelConverter;
    QString m_path;
    QString m_delim;
    QString m_endOfLine;
public:
    ConverterOptions(QString path="",QString delim ="", QString eol = ""):m_path(path), m_delim(delim), m_endOfLine(eol){}
    QString getPath() {return m_path==""?"":m_path+"/";}
    QString getDelim() {return m_delim;}
    QString getEndOfLine() {return m_endOfLine;}
    void setPath(QString path){m_path = path;}
    void setDelim(QString delim){m_delim = delim;}
    void setEndOfLine(QString eol){m_endOfLine = eol;}
};

class SqlModelConverter
{
public:
    SqlModelConverter(QString path="", QString delim = ",",
                      QString endOfLine = "\n");
    SqlModelConverter(ConverterOptions);
    void sqlToCsv(const QVector<QSqlTableModel*> &models, const QStringList &tablesToConvert, QHash<QString, QString>& result);
    ConverterOptions options;
};

#endif // SQLMODELCONVERTER_H
