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

    //name is not on_ because qt doesn't like it
    void onDbTablesView_clicked();

    void on_TabDatabase_clicked();

    void on_TabCSV_clicked();

    void on_TabExport_clicked();

    void on_TabSettings_clicked();

    void on_ButtonOpenNewDB_clicked();

    void on_ButtonExportDBtoCSV_clicked();

    void on_ButtonOpenNewCSV_clicked();

private:
    Ui::MainWindow *ui;
    bool dbWasLoad = false;
    bool csvWasLoad = false;
    SqlModelConverter converter;
};

#endif // MAINWINDOW_H
