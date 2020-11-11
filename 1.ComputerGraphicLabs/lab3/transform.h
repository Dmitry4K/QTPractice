#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<QMatrix4x4>
#include<QVector4D>


class Transform{
public:
    static QMatrix4x4* scale(float scale);
    static QMatrix4x4* rotationX(float angle);
    static QMatrix4x4* rotationY(float angle);
    static QMatrix4x4* rotationZ(float angle);
    static QMatrix4x4* rotation(float angleX, float angleY, float angleZ);
    static QMatrix4x4* rotationAndScale(float angleX, float angleY, float angleZ, float scale);
    static QMatrix4x4* projectionXY();
    static QMatrix4x4* moveOn(float dx, float dy, float dz);
    static QPointF toPointF( QVector4D);
    static QVector4D toIzometric(QVector4D, QVector4D);
    static bool isVisiable(const QVector4D& , const QVector4D&);
    static float scalingByWindow(int d_w, int d_h, int n_w, int n_h);
    static float angleBetween(const QVector4D&, const QVector4D&);
    static float scalarMultiplictaion(const QVector4D& , const QVector4D&);
    static float sizeOfVector(const QVector4D&);
};
#endif // TRANSFORM_H
