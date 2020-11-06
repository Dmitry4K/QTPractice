#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QMatrix4x4>
#include <QVector4D>

#include "transform.h"
#include "abstractpolygon3d.h"
class Transformer
{
public:
    Transformer();
    QVector4D camera;
    QMatrix4x4* getTransform();
    QPointF vectorProjection(QVector4D v);
    void setRotationX(float angle);
    void setRotationY(float angle);
    void setRotationZ(float angle);
    void setScale(float scale);
    bool isIzometric = true;
    void transformateVector(QVector4D& vector);
    void transformatePolygon(AbstractPolygon3D* pol);
private:
    QMatrix4x4* prevMatrix = nullptr;
    bool ischanged = false;
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;
    float scale = 1.0f;

};

#endif // TRANSFORMER_H
