#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    hLayout->addWidget(view, 1);
    hLayout->addLayout(vLayout);

    slidersHBox->setAlignment(Qt::AlignTop);
    lightingSettingsButton->setText("Light settings");

    angleXS->setInvertedAppearance(true);
    angleYS->setInvertedAppearance(true);
    angleZS->setInvertedAppearance(true);
    precisS->setInvertedAppearance(false);
    angleXS->setRange(0,360);
    angleYS->setRange(0,360);
    angleZS->setRange(0,360);
    precisS->setRange(3, 200);
    precisS->setSingleStep(1);
    precisS->setValue(100);

    angleXS->setSingleStep(1);
    angleYS->setSingleStep(1);
    angleZS->setSingleStep(1);

    izometricCB->setText("Izometric");
    hidebackCB->setText("Hide back");
    rotationLbl->setText("Rotation angles");
    enableLight->setText("Lighting");

    hidebackCB->setChecked(true);
    izometricCB->setChecked(true);
    enableLight->setChecked(false);

    vLayout->addWidget(izometricCB);
    vLayout->addWidget(hidebackCB);
    vLayout->addWidget(enableLight);
    vLayout->addWidget(precisS);
    vLayout->addWidget(rotationLbl);

    slidersHBox->addWidget(angleXS);
    slidersHBox->addWidget(angleYS);
    slidersHBox->addWidget(angleZS);
    //slidersHBox->addWidget(precisS);

    vLayout->addLayout(slidersHBox);
    vLayout->addWidget(lightingSettingsButton);

    QObject::connect(angleXS, SIGNAL(valueChanged(int)),
                        view, SLOT(rotationX(int)));
    QObject::connect(angleYS, SIGNAL(valueChanged(int)),
                        view, SLOT(rotationY(int)));
    QObject::connect(angleZS, SIGNAL(valueChanged(int)),
                        view, SLOT(rotationZ(int)));
    QObject::connect(izometricCB, SIGNAL(stateChanged(int)),
                        view, SLOT(showingChange(int)));
    QObject::connect(hidebackCB, SIGNAL(stateChanged(int)),
                        view, SLOT(hidingChange(int)));
    QObject::connect(precisS, SIGNAL(valueChanged(int)),
                        view, SLOT(changePrecision(int)));
    QObject::connect(enableLight, SIGNAL(stateChanged(int)),
                     view, SLOT(lightEnabling(int)));
    QObject::connect(lightingSettingsButton, SIGNAL(released()),
                     view, SLOT(relesedButtonLightSettings()));

}
