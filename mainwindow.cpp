#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DbManager.h"

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
    DbManager db("C:\\Users\\Pavel\\mydatabase.sqlite");
    QSqlTableModel *model = db.getModel();
    model->setTable("Product");
    model->select();
    ui->tableView->setModel(model);
}
