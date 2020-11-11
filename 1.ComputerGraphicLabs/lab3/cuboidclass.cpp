#include "cuboidclass.h"
#include <QVector>
#include <QLine>

CuboidClass::CuboidClass(float l, float w, float h) :
    AbstractPaintitng3D(),
    length (l),
    width(w),
    height(h)
{
    setSize(l, w, h);

}
/*
void CuboidClass::calculateLines(){
    lines->push_back({points[0], points[1]});
    lines->push_back({points[1], points[2]});
    lines->push_back({points[2], points[3]});
    lines->push_back({points[3], points[0]});
    lines->push_back({points[4], points[5]});
    lines->push_back({points[5], points[6]});
    lines->push_back({points[6], points[7]});
    lines->push_back({points[7], points[4]});
    lines->push_back({points[4], points[0]});
    lines->push_back({points[5], points[1]});
    lines->push_back({points[6], points[2]});
    lines->push_back({points[7], points[3]});
}*/

void CuboidClass::setSize(float l, float w, float h){
    points[0] = {(-1.0f * w/2.0f), (-1.0f * h/2.0f), l/2.0f          , 1};
    points[1] = {(-1.0f * w/2.0f), h/2.0f          , l/2.0f          , 1};
    points[2] = {w/2.0f          , h/2.0f          , l/2.0f          , 1};
    points[3] = {w/2.0f          , (-1.0f * h/2.0f), l/2.0f          , 1};
    points[4] = {(-1.0f * w/2.0f), (-1.0f * h/2.0f), (-1.0f * l/2.0f), 1};
    points[5] = {(-1.0f * w/2.0f), h/2.0f          , (-1.0f * l/2.0f), 1};
    points[6] = {w/2.0f          , h/2.0f          , (-1.0f * l/2.0f), 1};
    points[7] = {w/2.0f          , (-1.0f * h/2.0f), (-1.0f * l/2.0f), 1};
}

void CuboidClass::calculatePolygons() {
    addPolygon(new RectPolygon3D(points[0], points[1], points[2], points[3]));
    addPolygon(new RectPolygon3D(points[2], points[6], points[7], points[3]));
    addPolygon(new RectPolygon3D(points[7], points[6], points[5], points[4]));
    addPolygon(new RectPolygon3D(points[0], points[4], points[5], points[1]));
    addPolygon(new RectPolygon3D(points[1], points[5], points[6], points[2]));
    addPolygon(new RectPolygon3D(points[0], points[3], points[7], points[4]));
}



void CuboidClass::setLength(float l){
    length = l;
    setSize(length, width, height);
}
void CuboidClass::setWidth(float w){
    width = w;
    setSize(length, width, height);

}
void CuboidClass::setHeight(float h){
    height = h;
    setSize(length, width, height);

}
