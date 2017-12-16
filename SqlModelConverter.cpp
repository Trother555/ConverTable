#include "SqlModelConverter.h"

SqlModelConverter::SqlModelConverter(QString path, QString delim, QString endOfLine)
{
    options = ConverterOptions(path, delim, endOfLine);
}

SqlModelConverter::SqlModelConverter(ConverterOptions opts)
{
    options = opts;
}

void SqlModelConverter::sqlToCsv(const QVector<QSqlTableModel*> &models, const QStringList &tablesToConvert, QHash<QString, QString>& result)
{
    //цикл по всем таблицам из бд
    for(int i = 0; i<models.size();i++)
    {
        if(!tablesToConvert.contains(models[i]->tableName()))
            continue;
        auto fileContent = result.insert(models[i]->tableName(),"");
        //собираем имена полей
        int maxFieldInTable = models[i]->record(0).count();
        for(int k = 0; k<maxFieldInTable; k++)
        {
            *fileContent+=models[i]->record(0).field(k).name();
            *fileContent+=options.m_delim;
        }
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
