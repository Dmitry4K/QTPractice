#ifndef RECTPOLYGON3D_H
#define RECTPOLYGON3D_H

#include "abstractpolygon3d.h"
#include "polygon3d.h"
class RectPolygon3D : public Polygon3D
{
private:
    QVector4D additional;
public:
    RectPolygon3D(const QVector4D& first,
                  const QVector4D& second,
                  const QVector4D& third,
                  const QVector4D& fourth);

    QVector<QVector4D> getPoints() const override;
    void setPoints(QVector<QVector4D> &points) override;
    void paint(QPainter *painter, QPointF& c) override;
    ~RectPolygon3D(){};
};

#endif // RECTPOLYGON3D_H
