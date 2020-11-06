#include "sphereclass.h"
#include "polygon3d.h"
#include <QtMath>

SphereClass::SphereClass(float r, float p) :
    precision(p), radius(r)
{

}

void SphereClass::setPrecision(float p){
    if(p != precision){
        p = precision;
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

    QVector4D cur_point(0.0f, 0.0f, 0.0f, 1.0f);
    for(float gma = 0.0f; gma <= 2.0f * M_PI;gma += step){
        int i = 0 ;
        for(float phi = -M_PI_2;phi< M_PI_2; phi += step){
            cur_point.setX(radius * cosf(gma) * cosf(phi));
            cur_point.setY(radius * sinf(phi));
            cur_point.setZ(radius * sinf(gma) * cos(phi));
            if(arc_prev->size()){
                if(i < (arc_prev->size() - 1) && i > 0){
                 polygons->push_back(new Polygon3D(cur_point,arc_prev->at(i+1),arc_prev->at(i)));
                 polygons->push_back(new Polygon3D(arc_this->at(i-1),cur_point,arc_prev->at(i)));
                }
            }
            arc_this->push_back(cur_point);
            ++i;
        }
        float phi = M_PI_2;
        cur_point.setX(radius * cosf(gma) * cosf(phi));
        cur_point.setY(radius * sinf(phi));
        cur_point.setZ(radius * sinf(gma) * cos(phi));
        //if(arc_prev->size()){
          //  polygons->push_back(new Polygon3D(cur_point,arc_prev->at((i+1 == arc_prev->size() ? 0 : i+1)),arc_prev->at(i)));
        //}
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
            polygons->push_back(new Polygon3D(arc_first->at(i),arc_prev->at(i+1),arc_prev->at(i)));
            polygons->push_back(new Polygon3D(arc_first->at(i-1),arc_first->at(i),arc_prev->at(i)));
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
    QVector4D downp(radius, 0.0f, 0.0f, 1.0f);
    QVector4D upp(-radius, 0.0f, 0.0f, 1.0f);
    QVector4D point(0.0f, 0.0f, 0.0f, 1.0f);
    for(float gma = -M_PI_2+step; gma < M_PI_2; gma += step){
        float s_radius = radius * sinf(gma);
        for(float phi = 0.0f; phi <= 2.0f * M_PI; phi +=step){
            point.setX(s_radius * cosf(phi));
            point.setY(radius * cosf(gma));
            point.setZ(s_radius * sinf(phi));
            arc_this->push_back(point);
        }
        if(arc_prev->size()){

        } else {
            for(int i = 0;i<arc_this->size();++i){
                polygons->push_back(new Polygon3D(downp,
                                                  arc_this->at(i+1),
                                                  arc_this->at(i)));
            }
        }
        qSwap(arc_prev, arc_this);
        arc_this->clear();
    }
}
*/
