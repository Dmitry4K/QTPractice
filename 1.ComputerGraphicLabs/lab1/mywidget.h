#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QCheckBox>

#include"scalerclass.h"
#include"draggerclass.h"
#include"axesclass.h"
#include"functionclass.h"
#include"graphicprinterclass.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget();
protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    GraphicPrinterClass* Grapher = nullptr;
    //QLabel* lblState = nullptr;
    //QLabel* lblState2 = nullptr;
    QDoubleSpinBox* a = nullptr;
    QDoubleSpinBox* step = nullptr;
    QCheckBox* scaling =  nullptr;
private slots:
void redrawOnValueChange(double);
};

#endif // MYWIDGET_H
