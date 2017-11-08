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
    QObject::connect(ui->tabWidget, SIGNAL(click()), this, SLOT(onDbTablesView_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{

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
