#include "scenemodifier.h"
#include "transform.h"
#include "rectpolygon3d.h"
#include "widget3d.h"
#include <QPainter>
SceneModifier::SceneModifier(QWidget* c) :
    canvas(c)
{
    default_width = c->width();
    default_height = c->height();
}


void SceneModifier::paint(){
    QPen pen;
    QPointF center(canvas->width()/2.0, canvas->height()/2.0);
    transformer.camera = viewPoint;
    transformer.setScale(Transform::scalingByWindow(default_width, default_height, canvas->width(), canvas->height()));
    pen.setColor("black");
    pen.setWidth(2);
    pen.setDashOffset(10.0);
    QPainter painter(canvas);
    painter.setPen(pen);
    for(auto figure: figures){
        for(auto polygon : *figure->getPolygons()){
             transformer.transformatePolygon(polygon);
             if(Transform::isVisiable(polygon->getNormal(), QVector4D(0.0f, 0.0f, 1.0f, 0.0f))){
                pen.setWidth(3.0);
                painter.setPen(pen);
                polygon->paint(&painter, center);
             } else{
                 if(!hidingBack){
                     pen.setWidth(1.0);
                     painter.setPen(pen);
                     polygon->paint(&painter, center);
                 }
             }
        }
    }
}


void SceneModifier::addFigure(AbstractPaintitng3D* f){
    figures.push_back(f);
}

SceneModifier::~SceneModifier(){
    for(auto figure : figures){
        delete figure;
    }
}

void SceneModifier::setHidingBackSide(bool b){
    hidingBack = b;
}
void SceneModifier::setDefSizes(int w, int h){
    default_width = w;
    default_height = h;
}
