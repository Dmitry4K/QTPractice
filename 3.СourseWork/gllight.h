#ifndef GLLIGHT_H
#define GLLIGHT_H

#include <QColor>
#include <QVector4D>

class GLLight
{
public:
    QColor diffuse = Qt::black;
    QColor specular = Qt::black;
    QColor ambient = Qt::black;
    QVector4D direction = {0.0,0.0,0.0,1.0};
    GLLight();
};

#endif // GLLIGHT_H
