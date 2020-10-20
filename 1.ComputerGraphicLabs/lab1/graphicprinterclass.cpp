#include "graphicprinterclass.h"

GraphicPrinterClass::GraphicPrinterClass(AxesClass* ax, FunctionClass* func):
    Axes(ax),
    Function(func),
    Scaler(ax->getCanvas()),
    Dragger(ax->getCanvas())
{
    Scaler.push_back(ax);
    Scaler.push_back(func);
    Scaler.Center = ax->getCenter();
    Scaler.setDragger(&Dragger);
}

void GraphicPrinterClass::paint(){
    if(scaling){
        Scaler.scale();
    }
    Axes->setCenter(Axes->getCenter()+Dragger.delta(Axes->getCenter()));
    Axes->paint();
    Function->paint();
}

GraphicPrinterClass::~GraphicPrinterClass(){
    delete Axes;
    delete Function;
}
void GraphicPrinterClass::setScaling(bool p){
    scaling = p;
}
