#ifndef FUNCTIONCLASS_H
#define FUNCTIONCLASS_H

#include "axesclass.h"
#include "abstractpainting.h"

class FunctionClass : public AbstractPainting
{
public:
    FunctionClass(QWidget* c, AxesClass* a);
private:
    AxesClass* axes;
public:
    void paint() override;
    double A = 1;
    QColor Color = Qt::black;
    double Step = 0.1;
    QPointF function(const double angle);
    AxesClass* getAxes();
    void setAxes(AxesClass* a);
    ~FunctionClass(){}
};

#endif // FUNCTIONCLASS_H
