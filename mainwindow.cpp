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

    connect(ui->ButtonOpenNewDB,SIGNAL(clicked(bool)), this, SLOT(onButtonOpenNewDBClicked()));

    connect(ui->ButtonOpenNewCSV,SIGNAL(clicked(bool)), this, SLOT(onButtonOpenNewCSVClicked()));

    connect(ui->ButtonExportDBtoCSV,SIGNAL(clicked(bool)), this, SLOT(onButtonExportDBtoCSVClicked()));

    connect(ui->ButtonExportCSVtoDB,SIGNAL(clicked(bool)), this, SLOT(onButtonExportCSVtoDBClicked()));

    connect(ui->ButtonSetCsvPath,SIGNAL(clicked(bool)), this, SLOT(onButtonSetCsvPathClicked()));

    //connect(ui->TabCSV,SIGNAL(clicked(bool)), this, SLOT(onTabCSVClicked()));

    connect(ui->TabDatabase,SIGNAL(clicked(bool)), this, SLOT(onTabDatabaseClicked()));

    //connect(ui->TabExport,SIGNAL(clicked(bool)), this, SLOT(onTabExportClicked()));

    connect(ui->TabSettings,SIGNAL(clicked(bool)), this, SLOT(onTabSettingsClicked()));
    /*ui->widget->setStyleSheet("QWidget{background-color:rgb(165, 165, 165);}"
                              "QPushButton{background-color:rgb(165, 165, 165);}"
                              "QPushButton#TabDatabase{background-image:url(:/buttons/png/data-base.png)}");*/

}

MainWindow::~MainWindow()
{
    ui->listWidget->Clear();
    ui->tabWidget->Clear();
    if(dbManager!=nullptr)
        delete dbManager;
    delete ui;
}

void MainWindow::onTabDatabaseClicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/*void MainWindow::onTabCSVClicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}*/

//void MainWindow::onTabExportClicked()
//{
//    ui->stackedWidget->setCurrentIndex(1);
//}

void MainWindow::onTabSettingsClicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::onButtonOpenNewDBClicked()
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
        delete dbModel;
        dbWasLoad = false;
    }
    QString dbFileName = QFileDialog::getOpenFileName(this, "Db file", "", "SQLite files (*.sqlite)");
    if(dbFileName == "")
        return;
    dbModel = new DbModel(new DbManager(dbFileName));
    //Заполнить представление для таблиц бд
    ui->tabWidget->SetModel(dbModel);
    //Заполнить представление для списка таблиц с выбором таблиц на импорт
    ui->listWidget->SetModel(dbModel);
    dbWasLoad = true;
}

void MainWindow::onButtonExportDBtoCSVClicked()
{
    if(!dbWasLoad)
    {
        QMessageBox::warning(this,"Error","Db was not load");
        return;
    }

    auto tablesToSave = ui->listWidget->GetTablesToSave();
    QHash<QString, QString> files;
    converter.sqlToCsv(dbModel->getModels(), tablesToSave, files);
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

void MainWindow::onButtonSetCsvPathClicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.exec();
    converter.options.setPath(dialog.selectedFiles()[0]);
}

void MainWindow::onButtonOpenNewCSVClicked()
{
    if(csvWasLoad)
    {
        auto q = QMessageBox::question(this,
            "Closing table", "This will close currently open table. Do you want to continue?",
            QMessageBox::Yes|QMessageBox::No);
        if(q == QMessageBox::No)
            return;
        ui->tabWidget->Clear();
        ui->listWidget->Clear();
        if (dbModel)
            delete dbModel;
        if (csvModel)
            delete csvModel;
        csvWasLoad = false;
    }
    QStringList csvFileNames = QFileDialog::getOpenFileNames(this, "CSV file", "", "CSV files (*.csv)");
    if(csvFileNames.empty())
        return;

    csvModel = new CsvModel(csvFileNames);
    //Заполнить представление для таблиц бд
    ui->tabWidget->SetModel(csvModel);
    //Заполнить представление для списка таблиц с выбором таблиц на импорт
    ui->listWidget->SetModel(csvModel);
    csvWasLoad = true;
}

void MainWindow::onButtonExportCSVtoDBClicked()
{
    if(!csvWasLoad)
    {
        QMessageBox::warning(this,"Error","Csv was not load");
        return;
    }

    auto tablesToSave = ui->listWidget->GetTablesToSave();
    converter.csvToSql(csvModel->getModels(), tablesToSave);
    /*for(auto it = files.begin();it!=files.end();++it)
    {
        QFile file(converter.options.getPath() + it.key());
        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream( &file );
            stream << it.value();
        }
        file.close();
    }*/
}


