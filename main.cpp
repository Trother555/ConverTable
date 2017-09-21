#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    qApp->setStyleSheet("QGroupBox {\
                        border: 0;\
                        padding-left: -8;\
                        padding-right: -8;\
                        padding-bottom: -6;\
                        padding-top: -10;\
                    }");
    MainWindow w;
    w.show();
    return a.exec();
}
