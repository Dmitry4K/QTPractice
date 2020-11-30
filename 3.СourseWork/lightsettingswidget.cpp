#include "lightsettingswidget.h"
#include <QLabel>
#include <QtMath>
LightSettingsWidget::LightSettingsWidget()
{
    setMinimumSize(350, 180);
    setMaximumSize(minimumSize());
    cD->setModal(true);
    setWindowTitle("Light settings");
    cD->setCurrentColor(Qt::white);
    vLayout->addWidget(new QLabel("R"));
    vLayout->addWidget(sliderPositionX);
    vLayout->addWidget(new QLabel("Phi"));
    vLayout->addWidget(sliderPositionY);
    vLayout->addWidget(new QLabel("Gma"));
    vLayout->addWidget(sliderPositionZ);
    vLayout->addLayout(hLayout);
        hLayout->addWidget(pushButtonAmbient);
        hLayout->addWidget(pushButtonDiffuse);
        hLayout->addWidget(pushButtonSpecular);

    sliderPositionX->setRange(-500, 500);
    sliderPositionY->setRange(0, M_PI * 200);
    sliderPositionZ->setRange((-M_PI_2*100), (M_PI_2*1000));

    sliderPositionX->setSingleStep(1);
    sliderPositionY->setSingleStep(1);
    sliderPositionZ->setSingleStep(1);

    sliderPositionX->setValue(0);
    sliderPositionY->setValue(0);
    sliderPositionZ->setValue(0);

    QObject::connect(pushButtonAmbient, SIGNAL(released()),
                this, SLOT(getColorDialogA()));
    QObject::connect(pushButtonDiffuse, SIGNAL(released()),
                this, SLOT(getColorDialogD()));
    QObject::connect(pushButtonSpecular, SIGNAL(released()),
                this, SLOT(getColorDialogS()));
    QObject::connect(cD, SIGNAL(colorSelected(const QColor&))
                     , this, SLOT(lightChanged(const QColor&)));
}
void LightSettingsWidget::getColorDialogA(){
    cD->show();
    isAmbient = true;
}
void LightSettingsWidget::getColorDialogS(){
    cD->show();
    isSpecular = true;
}
void LightSettingsWidget::getColorDialogD(){
    cD->show();
    isDiffuse = true;
}

void LightSettingsWidget::lightChanged(const QColor&){
    if(isDiffuse){
        diffuse = cD->selectedColor();
        isDiffuse = false;
        pushButtonDiffuse->setText("Diffuse:"+cD->selectedColor().name());
    }
    if(isSpecular){
        specular = cD->selectedColor();
        isSpecular = false;
        pushButtonSpecular->setText("Specular:"+cD->selectedColor().name());
    }
    if(isAmbient){
        ambient = cD->selectedColor();
        isAmbient = false;
        pushButtonAmbient->setText("Ambient:"+cD->selectedColor().name());
    }
    emit lightColorChanged();
}
