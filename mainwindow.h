#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "DbManager.h"
#include <QMainWindow>
#include <QSqlTableModel>
#include "SqlModelConverter.h"
#include "dbmodel.h"
#include "CSVModel.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    DbManager* mngr = nullptr;
    QSqlTableModel* mdl = nullptr;
    ~MainWindow();

private slots:

    /**
     * @brief Функция обработки нажатия на кнопку выбора вкладки таблиц
     */
    void onTabDatabaseClicked();

    /**
     * @brief Функция обработки нажатия на кнопку выбора вкладки настроек
     */
    void onTabSettingsClicked();

    /**
     * @brief Функция обработки нажатия на кнопку открытия файла базы данных
     */
    void onButtonOpenNewDBClicked();

    /**
     * @brief Функция обработки нажатия на кнопку преобразования данных в формат CSV
     */
    void onButtonExportDBtoCSVClicked();

    /**
     * @brief Функция обработки нажатия на кнопку открытия файлов CSV
     */
    void onButtonOpenNewCSVClicked();

    /**
     * @brief Функция обработки нажатия на кнопку преобразования данных в формат базы данных
     */
    void onButtonExportCSVtoDBClicked();

    /**
     * @brief Функция обработки нажатия на кнопку выбора пути сохранения файлов
     */
    void onButtonSetCsvPathClicked();

private:
    Ui::MainWindow *ui;
    bool dbWasLoad = false;
    bool csvWasLoad = false;
    SqlModelConverter converter;
    AbstractTableModel* model = nullptr;
};

#endif // MAINWINDOW_H
