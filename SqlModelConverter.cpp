#include "SqlModelConverter.h"

void SqlModelConverter::sqlToCsv(QVector<QSqlTableModel*> models, QHash<QString, QString>& result)
{
    for(int i = 0; i<models.size();i++)
    {
        auto fileContent = result.insert(models[i]->tableName(),"");
        if(m_getFieldNames)
        {
            for(int j = 0; j<models[i]->rowCount(); j++)
            {
                int maxFieldInTable = models[i]->record(j).count();
                for(int k = 0; k<maxFieldInTable-1; k++)
                {
                    *fileContent+=models[i]->record(j).field(k).name();
                    *fileContent+=m_delim;
                }
                *fileContent+=m_endOfLine;
            }
        }

        for(int j = 0; j<models[i]->rowCount(); j++)
        {
            int maxFieldInTable = models[i]->record(j).count();
            for(int k = 0; k<maxFieldInTable-1; k++)
            {
                *fileContent+=models[i]->record(j).field(k).value().toString();
                *fileContent+=m_delim;
            }
            *fileContent+=models[i]->record(j).field(maxFieldInTable-1).value().toString();
            *fileContent+=m_endOfLine;
        }
    }
}
