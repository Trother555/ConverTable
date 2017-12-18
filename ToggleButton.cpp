#include "ToggleButton.h"
#include <QPushButton>
#include "ButtonGroup.h"

ToggleButton::ToggleButton(QWidget*p):QPushButton(p)
{
    this->setCheckable(true);
    this->setFlat(true);
    if(parent()!=nullptr)
        connect(this,SIGNAL(toggled(bool)), (ButtonGroup*)parent(), SLOT(SetSignleChecked()));
}
