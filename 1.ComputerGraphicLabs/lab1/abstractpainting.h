#ifndef ABSTRACTPAINTING_H
#define ABSTRACTPAINTING_H

#include<QWidget>
#include<QPointF>

const double DEFAULT_SCALE = 10; //n -> 1 point to n pixels
class AbstractPainting
{
private:
    QWidget* canvas;
    QPointF center;
    double scaleX = DEFAULT_SCALE;
    double scaleY = DEFAULT_SCALE;
    double minScale = 2;
    double maxScale = 1000.0;
public:
    AbstractPainting(QWidget* p);
    virtual void paint() = 0;
    void setCanvas(QWidget* p);
    QWidget* getCanvas();
    double getScaleX();
    double getScaleY();
    void setScaleX(double p);
    void setScaleY(double p);
    QPointF getCenter();
    void setCenter(const QPointF p);
    double getSingleStep();
    void setSingleStep(double);
    //~AbstractPainting(){}
};

#endif // ABSTRACTPAINTING_H
