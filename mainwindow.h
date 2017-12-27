#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "AbstractManager.h"
#include <QMainWindow>
#include <QSqlTableModel>
#include "SqlModelConverter.h"
#include "CSVTableModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //DbManager* mngr = nullptr;
    //QSqlTableModel* mdl = nullptr;
    ~MainWindow();

private slots:

    void on_TabDatabase_clicked();

    void on_TabCSV_clicked();

    void on_TabExport_clicked();

    void on_TabSettings_clicked();

    void on_ButtonOpenNewDB_clicked();

    void on_ButtonExportDBtoCSV_clicked();

    void on_ButtonOpenNewCSV_clicked();

    void on_ButtonSetCsvPath_clicked();

private:
    Ui::MainWindow *ui;
    bool TableWasLoad = false;
    SqlModelConverter converter;
    AbstractManager* manager = nullptr;

    CSVTableModel *csvTableModel;
};

#endif // MAINWINDOW_H
