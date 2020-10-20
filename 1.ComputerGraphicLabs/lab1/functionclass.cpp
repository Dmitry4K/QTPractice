#include "functionclass.h"
#include "axesclass.h"
#include<QPainter>
#include<QtMath>
FunctionClass::FunctionClass(QWidget* c, AxesClass* a) : AbstractPainting(c)
{
    setAxes(a);
}

AxesClass* FunctionClass::getAxes(){
    return axes;
}
void FunctionClass::setAxes(AxesClass* a){
    axes = a;
}

void FunctionClass::paint(){
    const double pi(4*atan(1));
    double end(pi/2);
    QPointF p1(function(0));
    QPainter ptr(getCanvas());
    QPen pen;
    pen.setColor(Color);
    pen.setWidth(2);
    ptr.setPen(pen);
    const QPointF& center = axes->getCenter();
    //(0;pi/2]
    for(double t(Step); t < end; t+= Step){
        QPointF p2(function(t));
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
    ptr.drawLine(p1+center, function(end)+center);
    //(pi/2;pi]
    end = pi;
    for(double t(pi/2); t < end; t+= Step){
        QPointF p2(function(t));
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
    ptr.drawLine(p1+center, function(end)+center);

    //(pi;1.5pi]
    end = 1.5*pi;
    for(double t(pi); t < end; t+= Step){
        QPointF p2(function(t));
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
    ptr.drawLine(p1+center, function(end)+center);

    //(1.5pi;2pi]
    end = 2*pi;
    for(double t(1.5*pi); t < end; t+= Step){
        QPointF p2(function(t));
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
    ptr.drawLine(p1+center, function(end)+center);
    //*/
}

QPointF FunctionClass::function(const double angle){
    return QPointF(A*getScaleX()*pow(cos(angle),3),A*getScaleY()*pow(sin(angle), 3) );
}
