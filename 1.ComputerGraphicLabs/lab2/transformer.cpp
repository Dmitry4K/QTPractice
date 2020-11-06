#include "transformer.h"

Transformer::Transformer()
{
}

QMatrix4x4* Transformer::getTransform(){
    if(ischanged || prevMatrix == nullptr){
        if(prevMatrix){
            delete prevMatrix;
        }
        auto* scal = Transform::scale(scale);
        auto* rotX = Transform::rotationX(rotationX);
        auto* rotY = Transform::rotationY(rotationY);
        auto* rotZ = Transform::rotationZ(rotationZ);
        prevMatrix = new QMatrix4x4();
        *prevMatrix =((*rotX) * (*rotY) * (*rotZ)) * (*scal);
        delete scal;
        delete rotX;
        delete rotY;
        delete rotZ;
    }
    ischanged = false;
    return prevMatrix;
}
QPointF Transformer::vectorProjection(QVector4D v){
    return Transform::toPointF(v);
}

void Transformer::setRotationX(float angle){
    ischanged = true;
    rotationX = angle;
}
void Transformer::setRotationY(float angle){
    ischanged = true;
    rotationY = angle;
}
void Transformer::setRotationZ(float angle){
    ischanged = true;
    rotationZ = angle;
}
void Transformer::setScale(float s){
    if(s != scale){
        ischanged = true;
        scale = s;
    }
}

void Transformer::transformateVector(QVector4D& vector){
    vector = (*getTransform()) * vector;
    if(isIzometric){
        vector = Transform::toIzometric(vector,camera);
    }
}
void Transformer::transformatePolygon(AbstractPolygon3D* pol){
    auto points = pol->getPoints();
    for(int i = 0;i<points.size();++i)
        transformateVector(points[i]);
    pol->setPoints(points);
}
