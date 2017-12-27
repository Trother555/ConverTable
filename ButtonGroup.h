#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H
#include <QWidget>


/**
 * @brief Виджет для группировки кнопок
 *
 */
class ButtonGroup : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор для преобразования(promotion) исходного класса qt
     *
     * @param виджет-родитель
     */
    ButtonGroup(QWidget*&);
public slots:
    /**
     * @brief Устанавливает в нажатое состояние только одну кнопку-потомок
     *
     */
    void SetSignleChecked();

};

#endif // BUTTONGROUP_H
