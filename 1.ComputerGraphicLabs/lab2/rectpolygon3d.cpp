#include "rectpolygon3d.h"
#include "transform.h"
RectPolygon3D::RectPolygon3D(const QVector4D& first,
                             const QVector4D& second,
                             const QVector4D& third,
                             const QVector4D& fourth) :
    Polygon3D(first, second, third),
    additional(fourth)
{
}

QVector<QVector4D> RectPolygon3D::getPoints() const{
    return QVector<QVector4D>({points[0], points[1], points[2], additional});
}

void RectPolygon3D::setPoints(QVector<QVector4D> &p) {
    points[0] = p[0];
    points[1] = p[1];
    points[2] = p[2];
    additional = p[3];
}
void RectPolygon3D::paint(QPainter *painter, QPointF& c){
    painter->drawLine(Transform::toPointF(points[0])+c, Transform::toPointF(points[1])+c);
    painter->drawLine(Transform::toPointF(points[1])+c, Transform::toPointF(points[2])+c);
    painter->drawLine(Transform::toPointF(points[2])+c, Transform::toPointF(additional)+c);
    painter->drawLine(Transform::toPointF(points[0])+c, Transform::toPointF(additional)+c);
}
