#include "splineclass.h"
#include <QMessageBox>
#include <QtMath>
#include <QDebug>
SplineClass::SplineClass()
{

}

bool isCatch(int x, int y, int px, int py){
    return (abs(x - px) < POINT_RADIUS && abs(y -py) < POINT_RADIUS);
}
QList<SplinePoint>::iterator SplineClass::findPoint(const QPointF& p){
    return findPoint(p.x(), p.y());
}
QList<SplinePoint>::iterator SplineClass::findPoint(int x, int y){
    QList<SplinePoint>::iterator i = points.begin();
    for(; i != points.end(); ++i){
        if(isCatch(x, y, i->x(), i->y())){
            return i;
        }
    }
    return i;
}
QList<SplinePoint>::iterator SplineClass::findPointOrRail(int x, int y){
    QList<SplinePoint>::iterator i = findPoint(x, y);
    if(i == points.end()){
        i = points.begin();
        for(; i != points.end(); ++i){
            if(!i->isRailNull()){
                if(isCatch(x, y, i->x() + i->getRail().x(),i->y() + i->getRail().y())){
                    return i;
                }
            }
        }
    }
    return i;
}

QList<SplinePoint>::iterator SplineClass::findPointOrRail(const QPointF& p){
    return findPointOrRail(p.x(), p.y());
}

QList<SplinePoint>& SplineClass::getPoints() {
    return points;
}

bool SplineClass::add(const QPointF& p){
    if(points.size() < 3){
        if(findPoint(p.x(), p.y()) == points.end()){
            SplinePoint t;
            t.setX(p.x());
            t.setY(p.y());
            points.push_back(t);
            emit lineChanged();
            return true;
        }
    }
    return false;
}

void SplineClass::clear(){
    points.clear();
    emit lineChanged();
}

bool SplineClass::isValid(){
    return points.size() == 3 && !points[0].isRailNull() && !points[2].isRailNull();
}

void SplineClass::calculatePolynoms(Polynom& fP, Polynom& sP, int p0, int p1, int p2, int r0, int r2){

    float& a1 = fP.a;
    float& a2 = sP.a;
    float& b1 = fP.b;
    float& b2 = sP.b;
    float& c1 = fP.c;
    float& c2 = sP.c;
    float& d1 = fP.d;
    float& d2 = sP.d;
    //qDebug() << p0 << ' ' << p1 << ' '<< p2 << ' '<<r0 << ' '<< r2 << '\n';
    d1 = p0; //+
    d2 = p1; //+
    c1 = r0;

    float n = -c1;
    float h = d2-d1-c1;
    float q = p2 - d2;
    float z = r2;
    float x = 3*q + 2*n - z;

    a1 = (x-5*h)/4;
    b1 = (9*h - x)/4;

    b2 = 3*a1 + b1;
    c2 = 3*a1 + 2*b1 - n;
    a2 = q - b2 - c2;
}
void SplineClass::calculate(){
    calculatePolynoms(fSegment.xPolynom,
                      sSegment.xPolynom,
                      points[0].x(), points[1].x(),
                      points[2].x(), points[0].getRail().x(), points[2].getRail().x());
    calculatePolynoms(fSegment.yPolynom,
                      sSegment.yPolynom,
                      points[0].y(), points[1].y(),
                      points[2].y(), points[0].getRail().y(), points[2].getRail().y());
}

int SplineClass::getPresicion(){
    return presicion;
}

void SplineClass::setPresicion(int p){
    presicion = p;
    emit lineChanged();
}
