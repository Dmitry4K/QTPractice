#include "polygon3d.h"
#include "transform.h"
#include <QPainter>

Polygon3D::Polygon3D(const QVector4D& first, const QVector4D& second, const QVector4D& third){
    points[0] = first;
    points[1] = second;
    points[2] = third;
}

QVector4D Polygon3D::getNormal() const{
    QVector4D first = points[1] - points[0];
    QVector4D second = points[2] - points[0];
    QVector4D res = QVector4D(QVector3D::crossProduct(first.toVector3D(), second.toVector3D()));
    res.setW(1);
    return res;
}

QVector<QVector4D> Polygon3D::getPoints() const {
    return QVector<QVector4D>({points[0], points[1], points[2]});
}


void Polygon3D::setPoints(QVector<QVector4D> &p) {
    points[0] = p[0];
    points[1] = p[1];
    points[2] = p[2];
}

void Polygon3D::paint(QPainter *painter, QPointF& c){
    QPointF* ppoints = new QPointF[3];
    ppoints[0] = Transform::toPointF(points[0])+c;
    ppoints[1] = Transform::toPointF(points[1])+c;
    ppoints[2] = Transform::toPointF(points[2])+c;
    painter->drawPolygon(ppoints, 3);
    delete[] ppoints;
}
