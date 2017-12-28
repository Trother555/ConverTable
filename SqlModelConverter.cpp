#include "SqlModelConverter.h"
#include "elemettype.h"
#include "CSVTableModel.h"

SqlModelConverter::SqlModelConverter(QString path, QString delim, QString endOfLine)
{
    options = ConverterOptions(path, delim, endOfLine);
}

SqlModelConverter::SqlModelConverter(ConverterOptions opts)
{
    options = opts;
}

void SqlModelConverter::sqlToCsv(const QVector<QSqlTableModel*> &&models, const QStringList &tablesToConvert, QHash<QString, QString>& result)
{
    //цикл по всем таблицам из бд
    for(int i = 0; i<models.size();i++)
    {
        if(!tablesToConvert.contains(models[i]->tableName()))
            continue;
        auto fileContent = result.insert(models[i]->tableName(),"");
        //собираем имена полей
        int maxFieldInTable = models[i]->record(0).count();
        for(int k = 0; k<maxFieldInTable-1; k++)
        {
            *fileContent+=models[i]->record(0).field(k).name();
            *fileContent+=options.m_delim;
        }
        *fileContent+=models[i]->record(0).field(maxFieldInTable-1).name();
        *fileContent+=options.m_endOfLine;
        //собираем поля
        for(int j = 0; j<models[i]->rowCount(); j++)
        {
            int maxFieldInTable = models[i]->record(j).count();
            for(int k = 0; k<maxFieldInTable-1; k++)
            {
                *fileContent+=models[i]->record(j).field(k).value().toString();
                *fileContent+=options.m_delim;
            }
            *fileContent+=models[i]->record(j).field(maxFieldInTable-1).value().toString();
            *fileContent+=options.m_endOfLine;
        }
    }
}

void SqlModelConverter::csvToSql(const QVector<QSqlTableModel*> &models, const QStringList &tablesToConvert)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName=options.getPath();
    for (int i=0; i<models.count()-1; ++i)
    {
        dbName+=models[i]->tableName()+"_";
    }
    dbName+=models[models.count()-1]->tableName()+".sqlite";
    db.setDatabaseName(dbName);
    if (!db.open())
    {
        qDebug("Failed to open test.db");
        return;
    }


    for (int modelNum = 0; modelNum < models.count(); ++modelNum)
    {
        if (tablesToConvert.indexOf(models[modelNum]->tableName()) >= 0)
        {
            QSqlQuery query;
            QVector<ElementType> columnTypes = dynamic_cast<CSVTableModel*>(models[modelNum])->getColumnTypes();

            QString queryString = QString("create table if not exists %1(").arg(models[modelNum]->tableName());
            for (int column = 0; column < models[modelNum]->columnCount(); ++column)
                queryString += QString("\"%1\" %2, ")
                        .arg(models[modelNum]->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString())
                        .arg(getTypeString(columnTypes[modelNum]));

            queryString.remove(queryString.length() - 2, 2);
            queryString += ")";
            if (!query.exec(queryString))
            {
                qDebug("Failed to create table.");
                qDebug(qPrintable(query.lastError().text()));
                return;
            }

            for (int i = 0; i < models[modelNum]->rowCount(); ++i)
            {
                queryString = QString("insert into %1 values(").arg(models[modelNum]->tableName());
                for (int j=0; j<models[modelNum]->columnCount(); ++j)
                {
                    if (columnTypes[j] == ElementType::STRING)
                    {
                        queryString+=QString("'%1'").arg(models[modelNum]->data(models[modelNum]->index(i,j), Qt::DisplayRole).toString());
                    }
                    else
                    {
                        queryString+=models[modelNum]->data(models[modelNum]->index(i,j), Qt::DisplayRole).toString();
                    }
                    queryString+=", ";
                }
                queryString.remove(queryString.length() - 2, 2);
                queryString += ")";

                if (!query.exec(queryString))
                {
                    qDebug("Failed to append table.");
                    qDebug(qPrintable(query.lastError().text()));
                    return;
                }
            }
        }
    }
    db.close();
}
