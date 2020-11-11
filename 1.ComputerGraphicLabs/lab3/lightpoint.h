#ifndef LIGHTPOINT_H
#define LIGHTPOINT_H

#include <QVector4D>
#include <QColor>
class LightPoint
{
    QVector4D postion = QVector4D(0.0f,0.0f,0.0f,1.0f);
    QVector4D normal = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
    float radius = 1.0f;
    float intensity = 0.0f;
    QColor color = Qt::white;
    float k = 0.5f;
public:
    void setK(float k);
    float getK() const;
    void setIntensity(float i);
    float getIntensity() const;
    void setColor(QColor c);
    QColor getColor() const;
    void setRadius(float b);
    float getRadius() const;
    void setPosition(const QVector4D& p);
    void setNormal(const QVector4D& n);
    LightPoint(const QVector4D& n);
    QVector4D getPosition() const;
    QVector4D getNormal() const;
    static QColor genColorByAngle(const LightPoint* l, float angle, QColor c);
};

#endif // LIGHTPOINT_H
