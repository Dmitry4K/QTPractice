#ifndef AXESCLASS_H
#define AXESCLASS_H

#include"abstractpainting.h"

class AxesClass :  public AbstractPainting
{
private:
    double singleStep = 1;
public:
    void paint() override;
    AxesClass(QWidget* p);
    double getSingleStep();
    void setSingleStep(double);
   // ~AxesClass();
};

#endif // AXESCLASS_H
