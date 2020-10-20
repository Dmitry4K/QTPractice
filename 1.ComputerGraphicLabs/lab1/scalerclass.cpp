#include "scalerclass.h"
#include "abstractpainting.h"

ScalerClass::ScalerClass(QWidget* can):
    canvas(can)
{
    width = canvas->width();
    height = canvas->height();
    startRes = width/height;
}
///*
void ScalerClass::scale(){
    if(!isScaled() || prevWitdh != canvas->width() || prevHeight != canvas->height()){
        double scaleX = canvas->width()/width;
        double scaleY = canvas->height()/height;
        for(auto el : *this){
            el->setScaleX(el->getScaleX()*scaleX);
            el->setScaleY(el->getScaleY()*scaleY);
            if(scalingByScrolling){
//                auto delta = Center - el->getCenter();
//                delta.setX(delta.x()*scaleX);
//              delta.setY(delta.y()*scaleY);
//                el->setCenter(el->getCenter()-delta);

            } else {
                auto newCenter = el->getCenter();
                newCenter.setX(newCenter.x()*scaleX);
                newCenter.setY(newCenter.y()*scaleY);
                el->setCenter(newCenter);
            }
      }
        if(!scalingByScrolling){
            DraggerScaling(scaleX, scaleY);
        }
        setWidth(getWidth()*scaleX);
        setHeight(getHeight()*scaleY);
    }
    prevWitdh = canvas->width();
    prevHeight = canvas->height();
    isscaled = true;
    scalingByScrolling = false;
}

double ScalerClass::getWidth() const{
    return width;
}
double ScalerClass::getHeight() const{
    return height;
}
void ScalerClass::setWidth(double p){
    if(p > 400.0*minScaling*startRes && p < 400.0*maxScaling*startRes){
        width = p;
    }
}
void ScalerClass::setHeight(double p){
    if(p > 400.0*minScaling && p < 400.0*maxScaling){
        height = p;
    }
}

bool ScalerClass::isScaled() const{
    return isscaled;
}
void ScalerClass::setScaling(bool p){
    isscaled = !p;
}
void ScalerClass::setScalingByScrolling(bool p){
    scalingByScrolling = p;
}

double ScalerClass::calculateScale(QWheelEvent* event) const{
    double k = (double)event->angleDelta().y()/100.0;
    if(k < 0){
        k = -k;
    } else if(k > 0){
        k = 1.0/k;
    } else if(k == 0){
        k = 1.0;
    }
    return k;
}

void ScalerClass::DraggerScaling(double scaleX, double scaleY){
    if(dragger != nullptr){
        //*
        dragger->Center.setX(double(dragger->Center.x())*scaleX);
        dragger->Center.setY(double(dragger->Center.y())*scaleY);
        dragger->End.setX(double(dragger->End.x())*scaleX);
        dragger->End.setY(double(dragger->End.y())*scaleY);
        dragger->Start.setX(double(dragger->Start.x())*scaleX);
        dragger->Start.setY(double(dragger->Start.y())*scaleY);
        //*/
    }
}
DraggerClass* ScalerClass::getDragger() const {
    return dragger;
}

void ScalerClass::setDragger(DraggerClass* drag){
    dragger = drag;
}
