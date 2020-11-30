#include "pointfieldwidget.h"
#include<QLabel>
#include<QSpacerItem>
PointFieldWidget::PointFieldWidget(int n)
{
    number = n;
    vMain->addWidget(new QLabel("x:"));
    vMain->addWidget(sbX);
    vMain->addWidget(new QLabel("y:"));
    vMain->addWidget(sbY);
    vMain->addWidget(new QLabel("z:"));
    vMain->addWidget(sbZ);
    sbX->setRange(-50, 50);
    sbY->setRange(-50, 50);
    sbZ->setRange(-50, 50);
    QObject::connect(sbX, SIGNAL(valueChanged(int)), this, SLOT(receiveChanges(int)));
    QObject::connect(sbY, SIGNAL(valueChanged(int)), this, SLOT(receiveChanges(int)));
    QObject::connect(sbZ, SIGNAL(valueChanged(int)), this, SLOT(receiveChanges(int)));
}
void PointFieldWidget::receiveChanges(int){
    emit valueChanged(number, QVector3D(sbX->value(), sbY->value(), sbZ->value()));
}

PointsWidget::PointsWidget(CardinalSplineClass* rsbcs) : Layout(this) {
    line = rsbcs;
    Layout.setSizeConstraint(QLayout::SetMinimumSize);
    Layout.setAlignment(Qt::AlignTop);
    QObject::connect(this, SIGNAL(newPoint(QVector3D)), line, SLOT(acceptNewPoint(QVector3D)));
    QObject::connect(this, SIGNAL(removeLast()), line, SLOT(removeLast()));
}

void PointsWidget::addField(){
    auto pfw = new PointFieldWidget(Points.size());
    Points.push_back(pfw);
    emit newPoint(QVector3D(0,0,0));
    QObject::connect(pfw, SIGNAL(valueChanged(int, QVector3D)), line, SLOT(acceptPointChanges(int, QVector3D)));
    Layout.addWidget(Points.back());
}
void PointsWidget::removeFiled(int index){
    if(Points.size() > index){
        auto it = Points.begin();
        for(int i = 0;i<index ;++i){
            ++it;
        }
        if(it != Points.end()){
            Layout.removeWidget(*it);
            Points.erase(it);
            delete *it;
            emit removeLast();
        }
    }
}
int PointsWidget::count(){
    return Points.size();
}
