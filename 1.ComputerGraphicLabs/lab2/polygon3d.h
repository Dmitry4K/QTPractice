#ifndef POLYGON_H
#define POLYGON_H

#include "abstractpolygon3d.h"

class Polygon3D : public AbstractPolygon3D
{
protected:
    QVector4D points[3];
public:
    Polygon3D(const QVector4D& first, const QVector4D& second, const QVector4D& third);
    QVector4D getNormal() const override;
    QVector<QVector4D> getPoints() const override;
    void setPoints(QVector<QVector4D> &points) override;
    void paint(QPainter *painter, QPointF& c) override;
    //~Polygon3D(){};
};

#endif // POLYGON_H
