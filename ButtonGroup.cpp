#include "ButtonGroup.h"
#include "ToggleButton.h"
ButtonGroup::ButtonGroup(QWidget *&p):QWidget(p)
{

}

void ButtonGroup::SetSignleChecked()
{
    ToggleButton *s = qobject_cast<ToggleButton*>(sender());
    if (s == nullptr)
        return;
    s->setChecked(true);
    for (QObject*c:this->children())
    {
        ToggleButton* tmp =qobject_cast<ToggleButton*>(c);
        if (tmp==nullptr)
            continue;
        if (tmp!=s)
        {
            bool state = tmp->blockSignals(true);
            tmp->setChecked(false);
            tmp->blockSignals(state);
        }
    }
}
