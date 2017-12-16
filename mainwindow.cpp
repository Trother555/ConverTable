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
        //exec yes-no dialog for clearing current connection
        ui->tabWidget->ClearAllTabs();
        dbWasLoad = false;
    }
    QString dbFileName = QFileDialog::getOpenFileName(this, "Файл базы данных", "", "SQLite files (*.sqlite)");
    DbManager *db = new DbManager(dbFileName);
    ui->tabWidget->SetDbAndFetch(db);
    //Set db list in settings
    for(auto name:db->getTables())
    {
        QListWidgetItem *it = new QListWidgetItem();
        it->setText(name);
        it->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
        it->setCheckState(Qt::Checked);
        ui->listWidget->addItem(it);
    }
    dbWasLoad = true;
}

void MainWindow::on_pushButton_4_clicked()
{
    onDbTablesView_clicked();
}

void MainWindow::on_pushButton_5_clicked()
{
    QHash<QString, QString> files;
    QStringList tablesToSave;
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        auto item = ui->listWidget->item(i);
        if(item->checkState() == Qt::Checked)
            tablesToSave.push_back(item->text());
    }
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

void MainWindow::on_pushButton_6_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.exec();
    converter.options.setPath(dialog.selectedFiles()[0]);
}
