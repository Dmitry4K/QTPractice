#include <QPainter>
#include <QPointF>
#include "axesclass.h"
#include "abstractpainting.h"


int Round(double a ){
    int res = a;
    if(a - (double)res >= 0.5){
        ++res;
    }
    return res;
}


AxesClass::AxesClass(QWidget* p) : AbstractPainting(p)
{
    setCenter(QPointF(p->width()/2.0, p->height()/2.0));
}
void AxesClass::paint() {
    QPainter ptr(getCanvas());
    ptr.setPen(Qt::blue);
    const double marging = 0.0;//25.0;
    const double arrow_shift = 5.0;
    const double slashSize = 8;

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    ptr.setPen(pen);

    QPointF a = getCenter();
    a.setX(marging);
    QPointF b = getCenter();
    b.setX(getCanvas()->width() - marging);
    QPointF current = getCenter();
    QPointF next = getCenter();
    current.setY(current.y() - slashSize/2);
    next.setY(next.y() + slashSize/2);
    int i = 1;
    for(double start(getCenter().x()+singleStep*getScaleX()); start < getCanvas()->width()-marging - 2*arrow_shift; start+=singleStep*getScaleX()){
        next.setX(start);
        current.setX(start);
        ptr.drawLine(next,current);
        if(i == 1){
            auto pos = next;
            pos.setY(pos.y() +15);
            pos.setX(pos.x() - getCanvas()->fontMetrics().boundingRect(QString::number(i)).width()/2);
            ptr.drawText(pos, QString::number(i));
        }
        if(i % 10 == 0){
            auto pos = next;
            pos.setY(pos.y() +15);
            pos.setX(pos.x() - getCanvas()->fontMetrics().boundingRect(QString::number(i)).width()/2);
            ptr.drawText(pos, QString::number(i));
        }
        ++i;
    }
    current = getCenter();
    next = getCenter();
    current.setY(current.y() - slashSize/2);
    next.setY(next.y() + slashSize/2);
    i = 1;
    for(double start(getCenter().x()-singleStep*getScaleX()); start > marging + 2*arrow_shift; start-=singleStep*getScaleX()){
        next.setX(start);
        current.setX(start);
        ptr.drawLine(next,current);
        if(i % 10 == 0){
            auto pos = next;
            pos.setY(pos.y() +15);
            pos.setX(pos.x() - getCanvas()->fontMetrics().boundingRect(QString::number(-i)).width()/2);
            ptr.drawText(pos, QString::number(-i));
        }
        ++i;
    }
    ptr.drawLine(a,b);//x

    QPointF c = b;
    c.setX(c.x() - arrow_shift);
    c.setY(c.y() - arrow_shift);
    ptr.drawLine(c,b);
    c.setY(c.y() + arrow_shift*2);
    ptr.drawLine(c,b);
    b.setX(b.x() - 10);
    b.setY(b.y() - 12);
    ptr.drawText(b, "X");
    // x arrow

    a.setX(getCenter().x());
    a.setY(marging);
    b.setX(getCenter().x());
    b.setY(getCanvas()->height() - marging);
    current = getCenter();
    next = getCenter();
    current.setX(current.x() - slashSize/2);
    next.setX(next.x() + slashSize/2);
    i = 1;
    for(double start(getCenter().y()+singleStep*getScaleY()); start < getCanvas()->height()-marging - 2*arrow_shift; start+=singleStep*getScaleY()){
        next.setY(start);
        current.setY(start);
        ptr.drawLine(next,current);
        if(i % 10 == 0){
            auto pos = current;
            pos.setX(pos.x() - getCanvas()->fontMetrics().boundingRect(QString::number(-i)).width()/2 - 15);
            pos.setY(pos.y() + getCanvas()->fontMetrics().boundingRect(QString::number(-i)).height()/2);
            ptr.drawText(pos, QString::number(-i));
        }
        ++i;
    }
    current = getCenter();
    next = getCenter();
    current.setX(current.x() - slashSize/2);
    next.setX(next.x() + slashSize/2);
    i=1;
    for(double start(getCenter().y()-singleStep*getScaleY()); start > marging + 2*arrow_shift; start-=singleStep*getScaleY()){
        next.setY(start);
        current.setY(start);
        ptr.drawLine(next,current);
        if(i == 1){
            auto pos = current;
            pos.setX(pos.x() - getCanvas()->fontMetrics().boundingRect(QString::number(i)).width()/2 - 15);
            pos.setY(pos.y() + getCanvas()->fontMetrics().boundingRect(QString::number(i)).height()/2);
            ptr.drawText(pos, QString::number(i));
        }
        if(i % 10 == 0){
            auto pos = current;
            pos.setX(pos.x() - getCanvas()->fontMetrics().boundingRect(QString::number(i)).width()/2 - 15);
            pos.setY(pos.y() + getCanvas()->fontMetrics().boundingRect(QString::number(i)).height()/2);
            ptr.drawText(pos, QString::number(i));
        }
        ++i;
    }
    ptr.drawLine(a,b);//y

    c = a;
    c.setX(c.x() - arrow_shift);
    c.setY(c.y() + arrow_shift);
    ptr.drawLine(c,a);
    c.setX(c.x() + arrow_shift*2);
    ptr.drawLine(c,a);
    //y arrow
    c.setX(c.x() + 4);
    c.setY(c.y() + 10);
    ptr.drawText(c, "Y");
    c = getCenter();
    c.setX(c.x() + 6);
    c.setY(c.y() - 6);
    ptr.drawText(c, "0");
}

double AxesClass::getSingleStep(){
    return singleStep;
}
void AxesClass::setSingleStep(double step){
    this->singleStep = step;
}
