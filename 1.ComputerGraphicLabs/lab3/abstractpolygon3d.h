#ifndef ABSTRACTPOLYGON3D_H
#define ABSTRACTPOLYGON3D_H
#include<QVector>
#include<QVector4D>
#include<QPainter>

class AbstractPolygon3D
{
public:
    AbstractPolygon3D();
    virtual QVector<QVector4D> getPoints() const = 0;
    virtual void setPoints(QVector<QVector4D>& points) =0;
    virtual QVector4D getNormal() const = 0;
    virtual void paint(QPainter*, QPointF&) {}
    virtual ~AbstractPolygon3D() {}
};

#endif // ABSTRACTPOLYGON3D_H
