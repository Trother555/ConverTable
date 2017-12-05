#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DbManager.h"
#include "DbTablesView.h"
#include <QFileDialog>
#include <QLabel>
#include "csvtable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onDbTablesView_clicked()
{
    if(dbWasLoad)
    {
        ui->tabWidget->ClearAllTabs();
        dbWasLoad = false;
    }
    QString dbFileName = QFileDialog::getOpenFileName(this, "Файл базы данных", "", "SQLite files (*.sqlite)");
    ui->tabWidget->SetDbAndFetch(new DbManager(dbFileName));
    dbWasLoad = true;
}



void MainWindow::on_TabDatabase_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_TabCSV_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_TabExport_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_TabSettings_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ButtonOpenNewDB_clicked()
{
    onDbTablesView_clicked();
}

void MainWindow::on_ButtonExportDBtoCSV_clicked()
{
    QHash<QString, QString> files;
    converter.sqlToCsv(ui->tabWidget->getModels(), files);
    for(auto it = files.begin();it!=files.end();++it)
    {
        QFile file(it.key());
        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream( &file );
            stream << it.value();
        }
        file.close();
    }
}

void MainWindow::on_ButtonOpenNewCSV_clicked()
{
    if(csvWasLoad)
    {
        ui->TableCSV->clear();
        dbWasLoad = false;
    }
    QString dbFileName = QFileDialog::getOpenFileName(this, "Файл базы данных", "", "SQLite files (*.sqlite)");
    ui->tabWidget->SetDbAndFetch(new DbManager(dbFileName));
    dbWasLoad = true;
    CSVTable table;
}
