#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H
#include <QPushButton>

/**
 * @brief Кнопка-переключатель
 *
 */
class ToggleButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор для преобразования(promotion) исходного класса qt
     *
     * @param виджет-родитель
     */
    ToggleButton(QWidget*);
};

#endif // TOGGLEBUTTON_H
