#ifndef TEST_CONVERTER_H
#define TEST_CONVERTER_H
#include <QtTest>

class Test_Converter: public QObject
{
    Q_OBJECT
private slots:
    void testConvertBothWaysSame();
};

#endif // TEST_CONVERTER_H
