#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DbManager.h"
#include "DbTablesView.h"

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

void MainWindow::on_pushButton_clicked()
{
    QString dbName = "C:\\Users\\Pavel\\mydatabase.sqlite";
    ui->tabWidget->SetDbManager(new DbManager(dbName));
    ui->tabWidget->FetchTables();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget->clearAllTabs();
}
