#ifndef TEST_CONVERTER_H
#define TEST_CONVERTER_H
#include <QtTest>

class test_converter: public QObject
{
    Q_OBJECT
private slots:
    void testConvertBothWaysSame();
};

#endif // TEST_CONVERTER_H
