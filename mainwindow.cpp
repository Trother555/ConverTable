#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DbManager.h"
#include "DbTablesView.h"
#include <QFileDialog>
#include <QLabel>
#include "csvtable.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    ui->listWidget->Clear();
    ui->tabWidget->Clear();
    delete ui;
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
    if(dbWasLoad)
    {
        auto q = QMessageBox::question(this,
            "Closing db", "This will close currently open db. Do you want to continue?",
            QMessageBox::Yes|QMessageBox::No);
        if(q == QMessageBox::No)
            return;
        ui->tabWidget->Clear();
        ui->listWidget->Clear();
        dbWasLoad = false;
    }
    QString dbFileName = QFileDialog::getOpenFileName(this, "Db file", "", "SQLite files (*.sqlite)");
    if(dbManager!=nullptr)
        delete dbManager;
    dbManager = new DbManager(dbFileName);
    //Заполнить представление для таблиц бд
    ui->tabWidget->SetAndFetch(dbManager);
    //Заполнить представление для списка таблиц с выбором таблиц на импорт
    ui->listWidget->SetAndFetch(dbManager);
    dbWasLoad = true;
}

void MainWindow::on_ButtonExportDBtoCSV_clicked()
{
    if(!dbWasLoad)
    {
        QMessageBox::warning(this,"Error","Db was not load");
        return;
    }

    auto tablesToSave = ui->listWidget->GetTablesToSave();
    QHash<QString, QString> files;
    converter.sqlToCsv(ui->tabWidget->getModels(), tablesToSave, files);
    for(auto it = files.begin();it!=files.end();++it)
    {
        QFile file(converter.options.getPath() + it.key());
        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream( &file );
            stream << it.value();
        }
        file.close();
    }
}

void MainWindow::on_ButtonSetCsvPath_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.exec();
    converter.options.setPath(dialog.selectedFiles()[0]);
}

void MainWindow::on_ButtonOpenNewCSV_clicked()
{
    if(csvWasLoad)
    {
        ui->TableCSV->clear();
        dbWasLoad = false;
    }
    /*QString dbFileName = QFileDialog::getOpenFileName(this, "Файл базы данных", "", "SQLite files (*.sqlite)");
    ui->tabWidget->SetDbAndFetch(new DbManager(dbFileName));
    dbWasLoad = true;
    CSVTable table;*/
}
