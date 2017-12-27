#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DbManager.h"
#include "CsvManager.h"
#include "DbTablesView.h"
#include <QFileDialog>
#include <QLabel>
#include "CSVTableModel.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    csvTableModel = new CSVTableModel();
    /*ui->widget->setStyleSheet("QWidget{background-color:rgb(165, 165, 165);}"
                              "QPushButton{background-color:rgb(165, 165, 165);}"
                              "QPushButton#TabDatabase{background-image:url(:/buttons/png/data-base.png)}");*/

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
    if(TableWasLoad)
    {
        auto q = QMessageBox::question(this,
            "Closing db", "This will close currently open db. Do you want to continue?",
            QMessageBox::Yes|QMessageBox::No);
        if(q == QMessageBox::No)
            return;
        ui->tabWidget->Clear();
        ui->listWidget->Clear();
        TableWasLoad = false;
    }
    QString dbFileName = QFileDialog::getOpenFileName(this, "Db file", "", "SQLite files (*.sqlite)");
    if(manager!=nullptr)
        delete manager;
    manager = new DbManager(dbFileName);
    //Заполнить представление для таблиц бд
    ui->tabWidget->SetAndFetch(manager);
    //Заполнить представление для списка таблиц с выбором таблиц на импорт
    ui->listWidget->SetAndFetch(manager);
    TableWasLoad = true;
}

void MainWindow::on_ButtonExportDBtoCSV_clicked()
{
    if(!TableWasLoad)
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
    /*ui->tabWidget->setModel(csvTableModel);

    if(csvWasLoad)
    {
        auto q = QMessageBox::question(this,
            "Closing db", "This will close currently open db. Do you want to continue?",
            QMessageBox::Yes|QMessageBox::No);
        if(q == QMessageBox::No)
            return;
        csvWasLoad = false;
    }
    QStringList csvFileNames = QFileDialog::getOpenFileNames(this, "CSV file", "", "CSV files (*.csv)");

    if (csvFileNames.isEmpty())
    {
        csvWasLoad = false;
        return;
    }
    for (const QString& x : csvFileNames)
    {

    }
    csvTableModel->readFromFile(csvFileName, ",");
    csvWasLoad = true;*/
    //ui->tabWidget->setModel(csvTableModel);

    if(TableWasLoad)
    {
        auto q = QMessageBox::question(this,
            "Closing csv", "This will close currently open csv. Do you want to continue?",
            QMessageBox::Yes|QMessageBox::No);
        if(q == QMessageBox::No)
            return;
        TableWasLoad = false;
    }
    QStringList csvFileNames = QFileDialog::getOpenFileNames(this, "CSV file", "", "CSV files (*.csv)");

    if(manager!=nullptr)
        delete manager;

    manager = new CsvManager(csvFileNames);
    //Заполнить представление для таблиц csv
    ui->tabWidget->SetAndFetch(manager);
    //Заполнить представление для списка таблиц с выбором таблиц на импорт
    ui->listWidget->SetAndFetch(manager);
    TableWasLoad = true;
}
