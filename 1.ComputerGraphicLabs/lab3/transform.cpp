#include "transform.h"
#include <QtMath>

QMatrix4x4* Transform::scale(float scale){
    return new QMatrix4x4(scale, 0, 0, 0,
                          0, scale, 0, 0,
                          0, 0, scale, 0,
                          0, 0, 0, 1);
}

QMatrix4x4* Transform::rotationX(float angle){
    return new QMatrix4x4(1, 0, 0, 0,
                          0, cos(angle), sin(angle), 0,
                          0, -sin(angle), cos(angle), 0,
                          0, 0, 0, 1);
}

QMatrix4x4* Transform::rotationY(float angle){
    return new QMatrix4x4(cos(angle), 0, -sin(angle), 0,
                          0, 1, 0, 0,
                          sin(angle), 0, cos(angle), 0,
                          0, 0, 0, 1);
}
QMatrix4x4* Transform::rotationZ(float angle){
    return new QMatrix4x4(cos(angle), sin(angle), 0, 0,
                          -sin(angle), cos(angle), 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
}

QMatrix4x4* Transform::projectionXY(){
    return new QMatrix4x4(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 0, 0,
                          0, 0, 0, 1);
}

QMatrix4x4* Transform::moveOn(float dx, float dy, float dz){
    return new QMatrix4x4(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          dx, dy, dz, 1);
}
QVector4D Transform::toIzometric(QVector4D v, QVector4D view){
    float x = (-1.0f * view.z() * v.x())/(v.z() - view.z());
    float y = (-1.0f * view.z() * v.y())/(v.z() - view.z());
    QVector4D res(x,y,v.z(),v.w());
    return res;
}

QPointF Transform::toPointF(QVector4D v){
    return QPointF(v.x(), v.y());
}
bool Transform::isVisiable(const QVector4D& a, const QVector4D& b){
    return scalarMultiplictaion(a,b) > 0;
}
float Transform::scalingByWindow(int d_w, int d_h, int n_w, int n_h){
    return ((n_w - d_w) >= (n_h - d_h)) ? (float)n_h / (float)d_h : (float)n_w / (float)d_w;
}

QMatrix4x4* Transform::rotation(float angleX, float angleY, float angleZ){
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float cosY = cos(angleY);
    float sinY = sin(angleY);
    float cosZ = cos(angleZ);
    float sinZ = sin(angleZ);
    return new QMatrix4x4(cosX*cosY, cosX*sinY*sinZ - sinX*cosZ, cosX*sinY*cosZ+sinX*sinZ,0 ,
                          sinX*cosY, sinX*sinY*sinZ + cosX*cosZ, sinX*sinY*cosZ-cosX*sinZ,0 ,
                          -sinY    , cosY*sinZ                 , cosY*cosZ               ,0 ,
                          0        , 0                         , 0                       ,1);
}

float Transform::angleBetween(const QVector4D& a, const QVector4D& b){
    return acosf(scalarMultiplictaion(a,b)/(sizeOfVector(a)*sizeOfVector(b)));
}

float Transform::scalarMultiplictaion(const QVector4D& a, const QVector4D& b){
    return a.x() * b.x() + a.y()*b.y() + a.z() * b.z();
}
float Transform::sizeOfVector(const QVector4D& a){
    return sqrtf(a.x()*a.x() + a.y() * a.y() + a.z() * a.z());
}

QMatrix4x4* Transform::rotationAndScale(float angleX, float angleY, float angleZ, float scale){
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float cosY = cos(angleY);
    float sinY = sin(angleY);
    float cosZ = cos(angleZ);
    float sinZ = sin(angleZ);
    return new QMatrix4x4(cosX*cosY*scale, (cosX*sinY*sinZ - sinX*cosZ)*scale, (cosX*sinY*cosZ+sinX*sinZ)*scale,0 ,
                          sinX*cosY*scale, (sinX*sinY*sinZ + cosX*cosZ)*scale, (sinX*sinY*cosZ-cosX*sinZ)*scale,0 ,
                          -sinY    *scale, (cosY*sinZ)*scale                 , (cosY*cosZ)*scale               ,0 ,
                          0        , 0                         , 0                       ,1);
}
