#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "DbManager.h"
#include <QMainWindow>
#include <QSqlTableModel>
#include "SqlModelConverter.h"
#include "dbmodel.h"
#include "CsvModel.h"


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

    void onTabDatabaseClicked();

    //void onTabCSVClicked();

    void onTabExportClicked();

    void onTabSettingsClicked();

    void onButtonOpenNewDBClicked();

    void onButtonExportDBtoCSVClicked();

    void onButtonOpenNewCSVClicked();

    void onButtonExportCSVtoDBClicked();

    void onButtonSetCsvPathClicked();

private:
    Ui::MainWindow *ui;
    bool dbWasLoad = false;
    bool csvWasLoad = false;
    SqlModelConverter converter;
    DbManager* dbManager = nullptr;
    DbModel* dbModel = nullptr;
    CsvModel* csvModel = nullptr;
};

#endif // MAINWINDOW_H
