#ifndef SCALERCLASS_H
#define SCALERCLASS_H

#include<QWidget>
#include<QVector>
#include<QWheelEvent>
#include<QPointF>

#include"abstractpainting.h"
#include"draggerclass.h"

class ScalerClass : public QVector<AbstractPainting*>
{
public:
    ScalerClass(QWidget* can);

private:
    QWidget* canvas = nullptr;
    double startRes;//uses for saving startring resolution;
    double width;
    double height;
    double minScaling = 0.01;
    double maxScaling = 5.0;
    double prevWitdh = 0.0;
    double prevHeight = 0.0;
    QVector<AbstractPainting*> paintings;
    bool isscaled = false;
    bool scalingByScrolling = false;
    void DraggerScaling(double scaleX, double scaleY);
    DraggerClass* dragger = nullptr;
public:
    QPointF Center = QPointF(0,0);
    void scale();
    double getWidth() const;
    double getHeight() const;
    void setWidth(double p);
    void setHeight(double p);
    bool isScaled() const;
    void setScaling(bool p);
    void setScalingByScrolling(bool p);
    double calculateScale(QWheelEvent* event) const;
    DraggerClass* getDragger() const;
    void setDragger(DraggerClass* drag);
};

#endif // SCALERCLASS_H
