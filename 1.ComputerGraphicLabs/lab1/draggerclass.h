#ifndef DRAGGERCLASS_H
#define DRAGGERCLASS_H

#include<QPointF>
#include<QWidget>

class DraggerClass
{
public:
    DraggerClass(QWidget* can);
    QWidget* canvas = nullptr;
    QPointF Start;
    QPointF End;
    QPointF Center;
    bool isDrag = false;
    QPointF delta(QPointF p) const;
    bool isDragged() const;
};

#endif // DRAGGERCLASS_H
