#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include<QWidget>
#include<QPointF>

class Additional
{
private:
    Additional();
public:
    static void Axes(QWidget* wdg, int width = 1);
    static QPointF function(const double angle, const double a);
    static void paintFunction(QWidget* wdg, const double a, const double step, QColor color = Qt::black);
};

#endif // ADDITIONAL_H
