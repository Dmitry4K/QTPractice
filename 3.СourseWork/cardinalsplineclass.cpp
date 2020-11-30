#include "cardinalsplineclass.h"
#include<QDebug>
CardinalSplineClass::CardinalSplineClass()
{

}

void CardinalSplineClass::setK(float nk){
    k = nk;
    emit splineChanged();
}
float CardinalSplineClass::getK(){
    return k;
}

void CardinalSplineClass::addPoint(const QVector3D p){
    points.push_back(p);
    emit splineChanged();
}

void CardinalSplineClass::calculate(){
    segments.clear();
    segments.reserve(points.size()-1);
    for(int i = 0;i<points.size()-1; ++i){
        segments.push_back(CardinalSplineSegmentClass());
    }
    if(points.size() > 1){
        preCalculation();
        for(int i = 0;i<segments.size()-1;++i){
            calculatePolynom(segments[i].xPolynom, segments[i+1].xPolynom, points[i].x(), points[i+2].x());
            calculatePolynom(segments[i].yPolynom, segments[i+1].yPolynom, points[i].y(), points[i+2].y());
            calculatePolynom(segments[i].zPolynom, segments[i+1].zPolynom, points[i].z(), points[i+2].z());
        }
        postCalculation();
    }
    qDebug() << "=================";
    for(int i = 0;i<segments.size(); ++i){
        auto& s = segments[i];
        qDebug() << s.xPolynom.a << ' ' << s.xPolynom.b << ' ' << s.xPolynom.c << ' ' << s.xPolynom.d;
        qDebug() << s.yPolynom.a << ' ' << s.yPolynom.b << ' ' << s.yPolynom.c << ' ' << s.yPolynom.d << "\n";
    }
    qDebug() << "=================";
}

void CardinalSplineClass::calculatePolynom(Polynom& fP,Polynom& sP, float p1, float p2){
    float m = sP.d - fP.d - fP.c;
    float q = sP.c - fP.c;
    fP.a = q - 2 * m;
    fP.b = 3 * m - q;
}

void CardinalSplineClass::preCalculation(){
    segments[0].xPolynom.c = k*(points[1].x()-points[0].x())/2;
    segments[0].yPolynom.c = k*(points[1].y()-points[0].y())/2;
    segments[0].zPolynom.c = k*(points[1].z()-points[0].z())/2;

    for(int i = 1;i<segments.size();++i){
        segments[i].xPolynom.c = k*(points[i+1].x()-points[i-1].x());
        segments[i].yPolynom.c = k*(points[i+1].y()-points[i-1].y());
        segments[i].zPolynom.c = k*(points[i+1].z()-points[i-1].z());
    }
    for(int i = 0;i<segments.size();++i){
        segments[i].xPolynom.d = points[i].x();
        segments[i].yPolynom.d = points[i].y();
        segments[i].zPolynom.d = points[i].z();
    }
}
void CardinalSplineClass::postCalculation(){
    calculateLastPolynom(segments.back().xPolynom, points.back().x(), points[points.size()-2].x());
    calculateLastPolynom(segments.back().yPolynom, points.back().y(), points[points.size()-2].y());
    calculateLastPolynom(segments.back().zPolynom, points.back().z(), points[points.size()-2].z());
}

void CardinalSplineClass::calculateLastPolynom(Polynom& pol, float pl, float pr){
    float t = k*(pl - pr)/2;
    float m = t - pol.c;
    float q = pl - pol.c - pol.d;
    pol.b = 3*q-m;
    pol.a = m-2*q;
}

void CardinalSplineClass::destroy(){
    segments.clear();
    points.clear();
    emit splineChanged();
}

QList<QVector3D>& CardinalSplineClass::getPoints(){
    return points;
}

QList<CardinalSplineClass::CardinalSplineSegmentClass>& CardinalSplineClass::getSegments(){
    return segments;
}

bool CardinalSplineClass::isValid(){
    return points.size() > 1;
}

void CardinalSplineClass::acceptPointChanges(int index, QVector3D p){
    auto it = points.begin();
    for(int i = 0;i<index;++i){
        ++it;
    }
    if(it != points.end()){
        it->setX(p.x());
        it->setY(p.y());
        it->setZ(p.z());
        emit splineChanged();
    }
}

void CardinalSplineClass::acceptNewPoint(QVector3D p){
    addPoint(p);
}

void CardinalSplineClass::acceptNewK(int p){
    setK((float)p/20);
}

void CardinalSplineClass::removeLast(){
    points.pop_back();
    emit splineChanged();
}
