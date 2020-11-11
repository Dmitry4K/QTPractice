#include "lightpoint.h"

LightPoint::LightPoint(const QVector4D& n) :
    normal(n)
{

}

void LightPoint::setPosition(const QVector4D& p){
    postion = p;
}

QVector4D LightPoint::getPosition() const{
    return postion;
}

void LightPoint::setNormal(const QVector4D& n){
    normal = n;
}

QVector4D LightPoint::getNormal() const{
    return normal;
}

void LightPoint::setRadius(float b){
    radius = b;
}
float LightPoint::getRadius() const{
    return radius;
}

QColor LightPoint::genColorByAngle(const LightPoint* l, float angle, QColor c){
    angle*=l->getRadius();
    QColor color = l->getColor();
    float intents = l->getIntensity();
    float blue = (color.blueF()*l->k+c.blueF()*(1-l->k))/ angle;
    float green = (color.greenF()*l->k+c.greenF()*(1-l->k)) / angle;
    float red = (color.redF()*l->k+c.redF()*(1-l->k)) / angle;
    color.setBlueF((blue > (1 -intents)*color.blueF()  ? (1 -intents)*color.blueF()  : blue));
    color.setRedF((red > (1 -intents)*color.redF() ? (1 -intents)*color.redF()  : red));
    color.setGreenF((green > (1 -intents)*color.greenF() ? (1 -intents)*color.greenF()  : green));
    return color;
}

void LightPoint::setColor(QColor c){
    color = c;
}
QColor LightPoint::getColor() const{
    return color;
}

void LightPoint::setIntensity(float i){
    intensity = i;
}
float LightPoint::getIntensity() const{
    return intensity;
}


void LightPoint::setK(float k){
    this->k = k;
}
float LightPoint::getK() const{
    return k;
}
