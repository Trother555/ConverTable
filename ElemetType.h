#ifndef ELEMETTYPE_H
#define ELEMETTYPE_H

#include <QString>

/**
 * @brief Тип элемента. Значения вводятся именно таким образом, чтобы свести
 * задачу нахождения типа столбца к задаче нахождения МАКСИМАЛЬНОГО индикатора
 * типа в столбце таблицы
 */
enum ElementType
{
    INTEGER = 0,
    REAL = 1,
    TEXT = 2
};

/**
 * @brief Возвращает тип элемента, представленного в строковом виде
 * @param val элемент
 * @return Идентификатор типа
 */
ElementType getType(QString val);

/**
 * @brief Возвращает строковое представление указанного типа в соответствии со стандартами SQLITE
 * @param type
 * @return
 */
QString getTypeString(ElementType type);


#endif // ELEMETTYPE_H
