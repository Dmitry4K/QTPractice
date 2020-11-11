#ifndef ABSTRACTPAINTITNG3D_H
#define ABSTRACTPAINTITNG3D_H

#include<QWidget>
#include<QVector4D>
#include<QVector>
#include<QPair>
#include<QPainter>
#include<QMatrix4x4>

#include"abstractpolygon3d.h"
class AbstractPaintitng3D
{
protected:
    void addPolygon(AbstractPolygon3D*);
    bool isChanged = false;
   // QVector<QPair<QVector4D, QVector4D>>* lines = nullptr;
    QVector<AbstractPolygon3D*>* polygons = nullptr;
public:
    QColor Color = Qt::white;
    QColor FrameColor = Qt::black;
    QVector<AbstractPolygon3D*>* getPolygons();
    virtual void calculatePolygons() = 0;
    AbstractPaintitng3D();
    virtual ~AbstractPaintitng3D();
};

#endif // ABSTRACTPAINTITNG3D_H
