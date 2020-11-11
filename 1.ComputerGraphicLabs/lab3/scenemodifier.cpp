#include "scenemodifier.h"
#include "transform.h"
#include "rectpolygon3d.h"
#include "widget3d.h"
#include <QPainter>
#include <QtMath>
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
    QPainter painter(canvas);
    //painter.setPen(pen);
    for(auto* figure: figures){
        for(auto polygon : *figure->getPolygons()){
             transformer.transformatePolygon(polygon);
                if(!hidingBack || Transform::isVisiable(polygon->getNormal(), QVector4D(0.0f, 0.0f, 1.0f, 0.0f))){
                    if(!enableLight){
                        pen.setWidth(1.0);
                        painter.setPen(figure->FrameColor);
                    }else{
                        float lightAngle = Transform::angleBetween(polygon->getNormal(), lightPoint.getNormal());                     pen.setWidth(1.0);
                        QColor color = LightPoint::genColorByAngle(&lightPoint, lightAngle, figure->Color);
                        painter.setBrush(color);
                        pen.setColor(color);
                        painter.setPen(pen);
                    }
                    polygon->paint(&painter, center);
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

void SceneModifier::setLightPoint(const LightPoint& lp){
    lightPoint = lp;
}
void SceneModifier::setEnableLight(bool e){
    enableLight = e;
}
