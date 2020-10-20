#include "draggerclass.h"

DraggerClass::DraggerClass(QWidget* can):canvas(can)
{
    Start.setX(can->width()/2.0);
    Start.setY(can->height()/2.0);
    Center = End = Start;
}

QPointF DraggerClass::delta(QPointF p) const{
    return End - Start + Center - p;
}
bool DraggerClass::isDragged() const{
    return isDrag;
}

