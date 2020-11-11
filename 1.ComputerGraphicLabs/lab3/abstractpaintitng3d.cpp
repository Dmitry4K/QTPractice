#include "abstractpaintitng3d.h"

AbstractPaintitng3D::AbstractPaintitng3D()
{
}

AbstractPaintitng3D::~AbstractPaintitng3D(){
    //delete lines;
}
QVector<AbstractPolygon3D*>* AbstractPaintitng3D::getPolygons(){
    if(polygons){
        for(int i = 0;i<polygons->size();++i)
            delete polygons->at(i);
        delete polygons;
    }
    polygons = new QVector<AbstractPolygon3D*>;
    calculatePolygons();
    return polygons;
}

void AbstractPaintitng3D::addPolygon(AbstractPolygon3D* p){
    polygons->push_back(p);
}
