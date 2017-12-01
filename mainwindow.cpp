#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DbManager.h"
#include "DbTablesView.h"
#include <QFileDialog>
#include <QLabel>

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
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::on_pushButton_4_clicked()
{
    onDbTablesView_clicked();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString fileContent = converter.sqlToCsv(ui->tabWidget->getModels());

}
