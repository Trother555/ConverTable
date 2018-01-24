#include "test_converter.h"
#include "SqlModelConverter.h"
#include "DbModel.h"
#include "CSVModel.h"
#include "test_helpers.h"

void Test_Converter::testConvertBothWaysSame()
{
    QStringList names;
    for (int i=1; i<=3; ++i)
    {
        names << QString(":/database/Tests/csv_input/test%1.csv").arg(i);
    }

    CSVModel csvModel(names);

    SqlModelConverter converter("./");

    converter.csvToSql(csvModel.getModels(), QStringList() << "test1" << "test2" << "test3");

    DbModel dbModel(new DbManager("./test1_test2_test3.sqlite"));

    QHash<QString, QString> files;
    converter.sqlToCsv(dbModel.getModels(), QStringList() << "test1" << "test2" << "test3", files);
    for (auto it = files.begin(); it!=files.end();++it)
    {
        QFile file("./" + it.key() + ".csv");
        file.remove();

        QVERIFY2(file.open(QIODevice::WriteOnly | QIODevice::Text), "Error in open CSV file to write data from DB");

        QTextStream stream( &file );
        stream << it.value();

        file.close();
    }


    for (int i=1; i<=3; ++i)
    {
        QFile in(names[i-1]);

        QVERIFY2(in.open(QIODevice::ReadOnly | QIODevice::Text), "Error in open csv input file");


        QFile out(QString("./test%1.csv").arg(i));

        QVERIFY2(out.open(QIODevice::ReadOnly | QIODevice::Text), "Error in open csv output file");


        while (!in.atEnd() && !out.atEnd())
        {
            QByteArray inLine(in.readLine());

            QByteArray outLine(out.readLine());

            QVERIFY2(inLine == outLine, "Error in comparing in and out csv files");
        }

        in.close();
        out.close();

        out.remove();

        QVERIFY2(in.atEnd() || out.atEnd(), "Error in comparing length of in and out csv files");
    }
}
