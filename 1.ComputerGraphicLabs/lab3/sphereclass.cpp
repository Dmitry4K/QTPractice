#include "sphereclass.h"
#include "polygon3d.h"
#include <QtMath>

SphereClass::SphereClass(float r, float p) :
    precision(p), radius(r)
{

}

void SphereClass::setPrecision(float p){
    if(p != precision){
        precision = p;
        isChanged = true;
    }
}
void SphereClass::setRadius(float r){
    if(r != precision){
        r = precision;
        isChanged = true;
    }
}
float SphereClass::getPrecision() const{
    return precision;
}
float SphereClass::getRadius() const{
    return radius;
}
//*
void SphereClass::calculatePolygons(){
    QVector<QVector4D>* arc_prev = new QVector<QVector4D>;
    QVector<QVector4D>* arc_this = new QVector<QVector4D>;
    QVector<QVector4D>* arc_first = new QVector<QVector4D>;
    bool save_first = false;
    float ring_length = 2.0f * M_PI;
    float step = ring_length / precision;

    float cosGma;
    float sinGma;
    float cosPhi;
    float sinPhi;
    QVector4D cur_point(0.0f, 0.0f, 0.0f, 1.0f);
    for(float gma = 0.0f; gma <= 2.0f * M_PI;gma += step){
        int i = 0 ;
        cosGma = cosf(gma);
        sinGma = sinf(gma);
        for(float phi = -M_PI_2;phi< M_PI_2; phi += step){
            cosPhi = cosf(phi);
            sinPhi = sin(phi);
            cur_point.setX(radius * cosGma * cosPhi);
            cur_point.setY(radius * sinPhi);
            cur_point.setZ(radius * sinGma * cosPhi);
            if(arc_prev->size()){
                if(i < (arc_prev->size() - 1) && i > 0){
                 addPolygon(new Polygon3D(cur_point,arc_prev->at(i+1),arc_prev->at(i)));
                 addPolygon(new Polygon3D(arc_this->at(i-1),cur_point,arc_prev->at(i)));
                }
            }
            arc_this->push_back(cur_point);
            ++i;
        }
        float phi = M_PI_2;
        float cosPhi = cosf(phi);
        float sinPhi = sin(phi);
        cur_point.setX(radius * cosGma * cosPhi);
        cur_point.setY(radius * sinPhi);
        cur_point.setZ(radius * sinGma * cosPhi);
        arc_this->push_back(cur_point);
        if(!save_first){
            save_first = true;
            *arc_first = *arc_this;
        }
        qSwap(arc_prev, arc_this);
        arc_this->clear();
    }
    for(int i = 0;i<arc_first->size()-1;++i){
        if(i < arc_prev->size() - 1 && i > 0){
            addPolygon(new Polygon3D(arc_first->at(i),arc_prev->at(i+1),arc_prev->at(i)));
            addPolygon(new Polygon3D(arc_first->at(i-1),arc_first->at(i),arc_prev->at(i)));
        }
    }
    delete arc_prev;
    delete arc_this;
}
//*/
/*
void SphereClass::calculatePolygons(){
    QVector<QVector4D>* arc_prev = new QVector<QVector4D>;
    QVector<QVector4D>* arc_this = new QVector<QVector4D>;
    float step = M_PI_2 / precision;
    float phi = -M_PI_2 + step;
    QVector4D point(0,0,0,1);
    QVector4D maxY(0,radius, 0, 1);
    QVector4D minY(0, -radius, 0 ,1);
    float r;
    for(; phi <= M_PI_2-step; phi += step){
        float gma = step;
        r = radius * cosf(phi);
        float sinPhi = sin(phi);
        for(; gma <= 2*M_PI;gma += step){
            float cosGma = cos(gma);
            float sinGma = sin(gma);
            point.setX(r * cosGma);
            point.setY(radius * sinPhi);
            point.setZ(r * sinGma);
            arc_this->push_back(point);
        }
        if(arc_prev->size() == 0){
            for(int i = 0;i<arc_this->size(); ++i){
                addPolygon(new Polygon3D(arc_this->at(i),
                                                  arc_this->at((i+1==arc_this->size() ? 0 : i + 1)),
                                                  minY));
            }
        } else {

        }
        qSwap(arc_this, arc_prev);
        arc_this->clear();
    }
//*/
