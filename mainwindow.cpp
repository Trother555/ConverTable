#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DbManager.h"
#include "DbTablesView.h"
#include <QFileDialog>

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
    QString dbFileName = QFileDialog::getOpenFileName(this, "Файл базы данных", "", "SQLite files (*.sqlite)");
    ui->tabWidget->SetDbManager(new DbManager(dbFileName));
    ui->tabWidget->FetchTables();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget->clearAllTabs();
}
