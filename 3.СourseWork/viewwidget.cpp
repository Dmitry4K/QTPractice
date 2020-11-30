#include "viewwidget.h"
#include "glcuboid.h"
#include <QLabel>

ViewWidget::ViewWidget() :
    ssw(&surface)
{
    glw->Engine.addFigure(&surface);
    hLayout->addWidget(glw,1);
    hLayout->addLayout(vLayout);
        vLayout->addWidget(isHidingBack);
        vLayout->addWidget(isLigthing);
        vLayout->addWidget(new QLabel("Rotations"));
        vLayout->addLayout(hLayoutRotations);
            hLayoutRotations->addWidget(sliderRotX);
            hLayoutRotations->addWidget(sliderRotY);
            hLayoutRotations->addWidget(sliderRotZ);
        vLayout->addWidget(ligthSettings);

    hLayout->addWidget(&ssw);
    isHidingBack->setText("Hide back");
    isLigthing->setText("Enable Light");
    ligthSettings->setText("Light settings");

    sliderRotX->setRange(0,MAX_VALUE_SLIDER);
    sliderRotY->setRange(0,MAX_VALUE_SLIDER);
    sliderRotZ->setRange(0,MAX_VALUE_SLIDER);
    sliderRotX->setSingleStep(1);
    sliderRotY->setSingleStep(1);
    sliderRotZ->setSingleStep(1);

    sliderRotX->setInvertedAppearance(true);
    sliderRotY->setInvertedAppearance(true);
    sliderRotZ->setInvertedAppearance(true);
    ligthSettings->setEnabled(false);
    ligthSettings->setFixedHeight(40);
    QObject::connect(sliderRotX, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(sliderRotY, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(sliderRotZ, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(isHidingBack, SIGNAL(stateChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(isLigthing, SIGNAL(stateChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(ligthSettings, SIGNAL(clicked()),
                     this, SLOT(showLightSettings()));
    QObject::connect(lsw->sliderPositionX, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(lsw->sliderPositionY, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(lsw->sliderPositionZ, SIGNAL(valueChanged(int)),
                     this, SLOT(configChanged(int)));
    QObject::connect(lsw, SIGNAL(lightColorChanged()),
                     this, SLOT(configChanged()));

    QObject::connect(&ssw.sbPrecision, SIGNAL(valueChanged(int)), &surface, SLOT(recievePrecision(int)));
    QObject::connect(&surface, SIGNAL(surfaceChanged()), this, SLOT(configChanged()));
}

float f1(int v){
    return (float)v*360/MAX_VALUE_SLIDER;
}
float f2(int v){
    return (float)v;
}
QVector4D f3(float r ,float angleX, float angleZ){
    QVector4D res;
    res.setX(r * sinf(angleZ) * cosf(angleX));
    res.setY(r * sinf(angleZ) * sinf(angleX));
    res.setZ(r * cosf(angleZ));
    res.setW(1.0);
    return res;
}
void ViewWidget::configChanged(){
    glw->Engine.setRotation(f1(sliderRotX->value()),
                             f1(sliderRotY->value()),
                             f1(sliderRotZ->value()));
    glw->Engine.setHidingBack(isHidingBack->isChecked());
    //isIzomteric->isChecked() ? glw->Engine.setIzomtericProjection() : glw->Engine.setOrthoProjection();
    ligthSettings->setEnabled(isLigthing->isChecked());

    if(isLigthing->isChecked()){
        surface.setMode(MATERIAL);
        glw->Engine.setHidingBack(true);
        isHidingBack->setEnabled(false);
        isHidingBack->setChecked(true);
        glw->Engine.setLightEnabled(true);
    } else{
        surface.setMode(FRAME);
        glw->Engine.setLightEnabled(false);
        isHidingBack->setEnabled(true);
    }
    glw->Engine.light.direction = f3((float)lsw->sliderPositionX->value()/100, (float)lsw->sliderPositionY->value()/100, (float)lsw->sliderPositionZ->value()/100);
    glw->Engine.light.ambient = lsw->ambient;
    glw->Engine.light.specular = lsw->specular;
    glw->Engine.light.diffuse = lsw->diffuse;
    glw->updateGL();
}
void ViewWidget::configChanged(int){
    configChanged();
}
ViewWidget::~ViewWidget(){
}

void ViewWidget::showLightSettings(){
    lsw->show();
}
