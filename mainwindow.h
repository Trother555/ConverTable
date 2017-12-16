#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "DbManager.h"
#include <QMainWindow>
#include <QSqlTableModel>
#include "SqlModelConverter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    DbManager* mngr = nullptr;
    QSqlTableModel* mdl = nullptr;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //name is not on_ because qt doesn't like it
    void onDbTablesView_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    bool dbWasLoad = false;
    SqlModelConverter converter;
};

#endif // MAINWINDOW_H
