#ifndef SQLMODELCONVERTER_H
#define SQLMODELCONVERTER_H

#include <QString>
#include <QtSql>

/**
 * @brief Класс настроек конвертера SqlModelConverter
 *
 */
class ConverterOptions
{
    friend class SqlModelConverter;
    QString m_path; /**< TODO: describe */
    QString m_delim; /**< TODO: describe */
    QString m_endOfLine; /**< TODO: describe */
public:
    /**
     * @brief Конструктор настроек
     *
     * @param path Путь для сохранения csv-файлов, сформированных из бд
     * @param delim Разделитель в csv-файле
     * @param eol Символ конца строки в csv-файле
     */
    ConverterOptions(QString path="",QString delim ="", QString eol = ""):m_path(path), m_delim(delim), m_endOfLine(eol){}
    /**
     * @brief Геттер для path
     *
     * @return QString
     */
    QString getPath() {return m_path==""?"":m_path+"/";}
    /**
     * @brief Геттер для delim
     *
     * @return QString
     */
    QString getDelim() {return m_delim;}
    /**
     * @brief Геттер для eol
     *
     * @return QString
     */
    QString getEndOfLine() {return m_endOfLine;}
    /**
     * @brief Сеттер для path
     *
     * @param path
     */
    void setPath(QString path){m_path = path;}
    /**
     * @brief Сеттер для delim
     *
     * @param delim
     */
    void setDelim(QString delim){m_delim = delim;}
    /**
     * @brief Сеттер для eol
     *
     * @param eol
     */
    void setEndOfLine(QString eol){m_endOfLine = eol;}
};

/**
 * @brief Класс конвертера
 *
 */
class SqlModelConverter
{
public:
    /**
     * @brief Конструктор конвертера
     * Конструирует конвертер с заданными настройками
     *
     * @param path Путь для сохранения csv-файлов, сформированных из бд
     * @param delim Разделитель в csv-файле
     * @param endOfLine Символ конца строки в csv-файле
     */
    SqlModelConverter(QString path="", QString delim = ",",
                      QString endOfLine = "\n");
    /**
     * @brief Конструктор конвертера
     * Конструирует конвертер с заданными настройками
     *
     * @param ConverterOptions Настройки конвертера
     */
    SqlModelConverter(ConverterOptions);
    /**
     * @brief Преобразует таблицы sql в csv-файлы
     * Преобразует таблицы sql, заданные в форме моделей, в csv-файлы, согласно настройкам, установленным в конструкторе класса.
     *
     * @param models Массив моделей таблиц
     * @param tablesToConvert Список имён таблиц, для которых надо выполнить преобразование
     * @param result Словарь вида "Имя таблицы" - "содержимое соответствующего csv-файла"
     */
    void sqlToCsv(const QVector<QSqlTableModel*> &&models, const QStringList &tablesToConvert, QHash<QString, QString>& result);
    ConverterOptions options; /**< TODO: describe */
};

#endif // SQLMODELCONVERTER_H
