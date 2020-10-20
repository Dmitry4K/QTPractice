#include "mywidget.h"
#include"axesclass.h"
#include"functionclass.h"
#include<QPainter>
#include<QLabel>
#include<QPoint>
#include<QMessageBox>
#include<QMouseEvent>
#include<QWheelEvent>
#include<QGroupBox>

MyWidget::MyWidget() : QWidget()
{
    setMinimumWidth(320);
    setMinimumHeight(240);
    int startPostionY = 20;
    int startPositionX = 15;
    resize(960, 540);

    QGroupBox* box = new QGroupBox(this);
    box->resize(75,135);
    box->move(2,2);
    box->setTitle("OPTIONS");

    QLabel* lblA(new QLabel("a:", this));
    lblA->move(startPositionX,startPostionY);

    a = new QDoubleSpinBox(this);
    a->setRange(1,20);
    a->setSingleStep(0.1);
    a->setValue(5);
    a->move(startPositionX,startPostionY+=20);

    QLabel* lblStep(new QLabel("Step:", this));
    lblStep->move(startPositionX, startPostionY += 25);

    step = new QDoubleSpinBox(this);
    step->setRange(0.01, 10);
    step->setSingleStep(0.01);
    step->setValue(0.1);
    step->move(startPositionX, startPostionY += 20);

    QLabel* lblScaling(new QLabel("Scaling:", this));
    lblScaling->move(startPositionX,startPostionY += 25);
    scaling = new QCheckBox(this);
    scaling->move(startPositionX+=40,startPostionY);
    scaling->setChecked(true);

    connect(a, SIGNAL(valueChanged(double)),
    this, SLOT(redrawOnValueChange(double)));
    connect(step, SIGNAL(valueChanged(double)),
    this, SLOT(redrawOnValueChange(double)));

    auto axes = new AxesClass(this);
    Grapher = new GraphicPrinterClass(axes, new FunctionClass(this, axes));
}


void MyWidget::paintEvent(QPaintEvent*){
    Grapher->Function->A = a->value();
    Grapher->Function->Step = step->value();
    Grapher->Function->Color = Qt::red;
    Grapher->setScaling(scaling->isChecked());
    Grapher->paint();
}


void MyWidget::redrawOnValueChange(double){
    this->update();
}
void MyWidget::wheelEvent(QWheelEvent *event){
    double k = Grapher->Scaler.calculateScale(event);
    //lblState->setText(QString::number( Grapher->Scaler.getWidth()*k)+' '+QString::number( Grapher->Scaler.getHeight()*k)+ ' ' + QString::number(k));
    Grapher->Scaler.setWidth( Grapher->Scaler.getWidth()*k);
    Grapher->Scaler.setHeight( Grapher->Scaler.getHeight()*k);
    Grapher->Scaler.Center = event->position();
    //lblState2->setText(QString::number(event->position().x()) + ' ' + QString::number(event->position().y()));
    Grapher->Scaler.setScaling(true);
    Grapher->Scaler.setScalingByScrolling(true);

    update();
}
void MyWidget::mousePressEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
         Grapher->Dragger.Start = event->pos();
         Grapher->Dragger.Center =  Grapher->Axes->getCenter();
    }
}
void MyWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
         Grapher->Dragger.End = event->pos();
         Grapher->Dragger.isDrag = true;
        update();
    }
}

