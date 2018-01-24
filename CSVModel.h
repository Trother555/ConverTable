#ifndef CSVMODEL_H
#define CSVMODEL_H

#include "AbstractDbModel.h"

/**
 * @brief Класс, хранящий в себе несколько моделей таблиц, прочитанных из CSV файлов
 *
 */
class CSVModel : QObject, public AbstractTableModel
{
    Q_OBJECT
    /**
     * @brief Хранящиеся модели
     */
    QVector<QSqlTableModel*> models;
public:
    /**
     * @brief Конструирует модель файлов CSV по выбраннм пользователем именам файлов
     *
     * @param names имена файлов для загрузки
     */
    CSVModel(const QStringList& names);

    /**
     * @brief Функция получения всех моделей таблиц из общей модели
     * @return все модели таблиц
     */
    const QVector<QSqlTableModel*>& getModels() const override;

    /**
     * @brief Деструктор
     */
    ~CSVModel(){}
};

#endif // CSVMODEL_H
