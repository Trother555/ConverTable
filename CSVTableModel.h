#ifndef CSVTABLE_H
#define CSVTABLE_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QByteArray>
#include <QAbstractTableModel>
#include <QtSql>

#include "ElemetType.h"

/**
 * @brief Класс, хранящий в себе информацию из CSV файла
 *
 */
class CSVTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    /**
     * @brief Переопределённая функция, возвразающая количество строк в модели
     * @param parent родитель
     * @return Количество строк в модели
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Переопределённая функция, возвразающая количество столбцов в модели
     * @param parent родитель
     * @return Количество столбцов в модели
     */
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Возвращает данные, хранящиеся по указанному индексу
     * @param index индекс модели
     * @param role роль элемента
     * @return Запрашиваемый элемент
     */
    virtual QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief Возвращает название указанного столбца таблицы
     * @param section номер столбца
     * @param orientation указывает, вертикальный или горизонтальный столбец имеется в виду
     * @param role роль
     * @return Название выбранного столбца
     */
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    /**
     * @brief Очищает модель
     */
    void reset();

    /**
     * @brief Конструктор
     * @param parent родитель
     */
    explicit CSVTableModel(QObject *parent = nullptr) : QSqlTableModel(parent){}

    /**
     * @brief Читает данные из файла в текущий объект
     * @param filename имя файла
     * @param sep разделитель
     * @return Успешность операции
     */
    bool readFromFile(const QString& filename, const QString& sep);

    /**
     * @brief Возвращает типы столбцов модели
     * @return Типы столбцов модели
     */
    const QVector<ElementType>& getColumnTypes() const;
signals:

public slots:

private:
    QList<QStringList> table;
    QStringList horizontalHeader;
    QVector<ElementType> columnTypes;

    /**
     * @brief Функция разбиения строки на подстроки в соответствии со стандартами CSV
     * @param row строка, которую требуется разбить на ячейки
     * @param sep разделитель
     * @param isFull возвращает true, если все ячейки строки прочитаны полностью и false, если данные последней ячейки неполны
     * @return Список строк - ячеек таблицы
     */
    static QStringList splitRow(const QString &row, const QString& sep, bool &isFull);
};











/**********************************************/
/*class CSVTable_old : public QObject
{
    Q_OBJECT
public:
    explicit CSVTable_old(QObject *parent) : QObject(parent){}
    ErrorCode read(const QString& filename, const QString& sep);

signals:

public slots:

private:
    QList<QStringList> table;
    QVector<ElementType> columnTypes;
    QStringList columnNames;
    QStringList splitRow(const QByteArray& row, const QString& sep);

    unsigned int rowCount, columnCount;
};*/
#endif // CSVTABLE_H
