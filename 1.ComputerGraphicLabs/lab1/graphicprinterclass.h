#ifndef GRAPHICPRINTERCLASS_H
#define GRAPHICPRINTERCLASS_H

#include"axesclass.h"
#include"functionclass.h"
#include"scalerclass.h"
#include"draggerclass.h"

class GraphicPrinterClass
{
private:
    bool scaling = true;
public:
    AxesClass* Axes;
    FunctionClass* Function;
    ScalerClass Scaler;
    DraggerClass Dragger;
    GraphicPrinterClass(AxesClass* ax, FunctionClass* func);
    void paint();
    void setScaling(bool);
    ~GraphicPrinterClass();
};

#endif // GRAPHICPRINTERCLASS_H
