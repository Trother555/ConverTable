#include "SqlModelConverter.h"

QHash SqlModelConverter::sqlToCsv(QVector<QSqlTableModel*> models)
{
    QHash result;

    for(int i = 0; i<models.size();i++)
    {
        if(m_getFieldNames)
        {
            for(int j = 0; j<models[i]->rowCount(); j++)
            {
                int maxFieldInTable = models[i]->record(j).count();
                for(int k = 0; k<maxFieldInTable-1; k++)
                {
                    result+=models[i]->record(j).field(k).name();
                    result+=m_delim;
                }
                result+=m_endOfLine;
            }
        }

        for(int j = 0; j<models[i]->rowCount(); j++)
        {
            int maxFieldInTable = models[i]->record(j).count();
            for(int k = 0; k<maxFieldInTable-1; k++)
            {
                result+=models[i]->record(j).field(k).value().toString();
                result+=m_delim;
            }
            result+=models[i]->record(j).field(maxFieldInTable-1).value().toString();
            result+=m_endOfLine;
        }
    }
    return result;
}
