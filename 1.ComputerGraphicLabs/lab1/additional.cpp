#include "additional.h"
#include <QPainter>
Additional::Additional()
{
}

void Additional::Axes(QWidget *wdg, int width){
    QPainter ptr(wdg);
    ptr.setPen(Qt::blue);
    const QPointF center(wdg->width() / 2.0, wdg->height() / 2.0);
    const double marging = 25.0;
    const double arrow_shift = 5.0;
    ptr.setPen(Qt::black);

    QPointF a = center;
    a.setX(marging);
    QPointF b = center;
    b.setX(wdg->width() - marging);
    ptr.drawLine(a,b);//x

    QPointF c = b;
    c.setX(c.x() - arrow_shift);
    c.setY(c.y() - arrow_shift);
    ptr.drawLine(c,b);
    c.setY(c.y() + arrow_shift*2);
    ptr.drawLine(c,b);
    b.setX(b.x() - 4);
    b.setY(b.y() - 12);
    ptr.drawText(b, "X");
    // x arrow

    a.setX(center.x());
    a.setY(marging);
    b.setX(center.x());
    b.setY(wdg->height() - marging);
    ptr.drawLine(a,b);//y

    c = a;
    c.setX(c.x() - arrow_shift);
    c.setY(c.y() + arrow_shift);
    ptr.drawLine(c,a);
    c.setX(c.x() + arrow_shift*2);
    ptr.drawLine(c,a);
    c.setX(c.x() + 4);
    ptr.drawText(c, "Y");
    //y arrow
}
QPointF Additional::function(const double angle, const double a){
    const double k = 5;
    return QPointF(a*k*pow(cos(angle),3),a*k*pow(sin(angle), 3) );
}

void Additional::paintFunction(QWidget* wdg, const double a, const double step, QColor color){
    //const double step(0.1);
    const double pi(4*atan(1));
    double end(pi/2);
    QPointF p1(Additional::function(0,a));
    QPainter ptr(wdg);
    ptr.setPen(color);
    const QPointF center(wdg->width() / 2.0, wdg->height() / 2.0);

    //(0;pi/2]
    for(double t(step); t < end; t+= step){
        QPointF p2(Additional::function(t, a));
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
    ptr.drawLine(p1+center, function(end, a)+center);

    //(pi/2;pi]
    end = pi;
    for(double t(pi/2); t < end; t+= step){
        QPointF p2(Additional::function(t, a));
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
    ptr.drawLine(p1+center, function(end, a)+center);

    //(pi;1.5pi]
    end = 1.5*pi;
    for(double t(pi); t < end; t+= step){
        QPointF p2(Additional::function(t, a));
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
    ptr.drawLine(p1+center, function(end, a)+center);

    //(1.5pi;2pi]
    end = 2*pi;
    for(double t(1.5*pi); t < end; t+= step){
        QPointF p2(Additional::function(t, a));
        ptr.drawLine(p1+center, p2+center);
        p1 = p2;
    }
    ptr.drawLine(p1+center, function(end, a)+center);
}
