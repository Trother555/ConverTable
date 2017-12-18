#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H
#include <QWidget>


class ButtonGroup : public QWidget
{
    Q_OBJECT
public:
    ButtonGroup(QWidget*&);
public slots:
    void SetSignleChecked();

};

#endif // BUTTONGROUP_H
