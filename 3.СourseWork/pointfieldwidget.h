#ifndef POINTFIELDWIDGET_H
#define POINTFIELDWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QString>
#include <QList>
#include "ruledsurfacebycardinalspline.h"
class PointFieldWidget : public QWidget
{
    Q_OBJECT
public:
    int number;
    QString text;
    QHBoxLayout* vMain = new QHBoxLayout(this);
    QSpinBox* sbZ = new QSpinBox;
    QSpinBox* sbX = new QSpinBox;
    QSpinBox* sbY = new QSpinBox;
    PointFieldWidget(int n);
public slots:
    void receiveChanges(int);
signals:
    void valueChanged(int i, QVector3D);
};

class PointsWidget : public QWidget{
    Q_OBJECT
    QList<PointFieldWidget*> Points;
    QVBoxLayout Layout;
    CardinalSplineClass* line = nullptr;
public:
    void addField();
    void removeFiled(int index);
    int count();
    PointsWidget(CardinalSplineClass* rsbcs);
public slots:
signals:
    void newPoint(QVector3D);
    void removeLast();
};

#endif // POINTFIELDWIDGET_H
