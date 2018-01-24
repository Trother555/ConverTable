#-------------------------------------------------
#
# Project created by QtCreator 2017-09-21T15:27:04
#
#-------------------------------------------------

QT       += core gui sql
QT	 += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += tests

    TARGET = ConverTable
    TEMPLATE = app
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
	main.cpp \
	mainwindow.cpp \
    DbManager.cpp \
    SqlModelConverter.cpp \
    DbNamesListView.cpp \
    ToggleButton.cpp \
    ButtonGroup.cpp \
    DbModel.cpp \
    AbstractDbModel.cpp \
    CSVTableModel.cpp \
    CSVModel.cpp \
    ElementType.cpp \
    DbTablesView.cpp \
    Tests/test_main.cpp

HEADERS += \
	mainwindow.h \
    DbManager.h \
    SqlModelConverter.h \
    DbNamesListView.h \
    ToggleButton.h \
    ButtonGroup.h \
    DbModel.h \
    AbstractDbModel.h \
    CSVTableModel.h \
    CSVModel.h \
    ElemetType.h \
    DbTablesView.h

FORMS += \
	mainwindow.ui

DISTFILES +=

RESOURCES += \
    res.qrc
tests{
    message(Configuring test build...)
    QT += testlib

    SOURCES -= main.cpp

    SOURCES += \
    Tests/test_dbmanager.cpp \
    Tests/test_dbnameslistview.cpp \
    Tests/test_helpers.cpp \
    Tests/test_converter.cpp

    HEADERS += \
    Tests/test_dbmanager.h \
    Tests/test_dbnameslistview.h \
    Tests/test_helpers.h \
    Tests/test_converter.h
}
