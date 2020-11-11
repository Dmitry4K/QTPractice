#include "widjetlightsettings.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QSizePolicy>
#include <QLabel>

WidjetLightSettings::WidjetLightSettings()
{
    setWindowTitle("Light settings");
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    QVBoxLayout* vLayoutLight = new QVBoxLayout();
    cD->setCurrentColor(Qt::white);
    sliderX->setRange(-MAX_VALUE_SLIDER, MAX_VALUE_SLIDER);
    sliderY->setRange(-MAX_VALUE_SLIDER, MAX_VALUE_SLIDER);
    sliderZ->setRange(-MAX_VALUE_SLIDER, MAX_VALUE_SLIDER);
    sliderIntensity->setRange(0.0f, MAX_VALUE_SLIDER-1);
    sliderRadius->setRange(MAX_VALUE_SLIDER/2, 5*MAX_VALUE_SLIDER);
    sliderK->setRange(0.0f, MAX_VALUE_SLIDER-1);
    sliderX->setSingleStep(1);
    sliderY->setSingleStep(1);
    sliderZ->setSingleStep(1);
    sliderK->setSingleStep(1);
    sliderIntensity->setSingleStep(1);
    sliderIntensity->setToolTip("choose intensity");
    sliderRadius->setValue(MAX_VALUE_SLIDER);
    sliderX->setValue(MAX_VALUE_SLIDER);
    sliderY->setValue(MAX_VALUE_SLIDER);
    sliderZ->setValue(MAX_VALUE_SLIDER);
    sliderK->setValue(MAX_VALUE_SLIDER/2);
    sliderIntensity->setValue(0);
    sliderIntensity->setInvertedAppearance(true);
    sliderRadius->setInvertedAppearance(true);
    hLayout->addLayout(vLayoutLight);
    vLayoutLight->addWidget(new QLabel("I - component"));
    vLayoutLight->addWidget(sliderX);
    vLayoutLight->addWidget(new QLabel("J - component"));
    vLayoutLight->addWidget(sliderY);
    vLayoutLight->addWidget(new QLabel("K - component"));
    vLayoutLight->addWidget(sliderZ);
    vLayoutLight->addWidget(new QLabel("Radius of Light"));
    vLayoutLight->addWidget(sliderRadius);
    vLayoutLight->addWidget(new QLabel("Intesity of Light"));
    vLayoutLight->addWidget(sliderIntensity);
    vLayoutLight->addWidget(new QLabel("Reflectivity"));
    vLayoutLight->addWidget(sliderK);
    vLayoutLight->addWidget(lightButton);
    lightButton->setText(cD->currentColor().name());
    QObject::connect(lightButton, SIGNAL(released()),
                this, SLOT(getColorDialog()));

    setMinimumWidth(this->width()/3.0f);
    setMaximumWidth(this->minimumWidth()*2.0f);
    setMinimumHeight(this->height()/1.5f);
    setMaximumHeight(this->minimumHeight());
}

void WidjetLightSettings::getColorDialog(){
    cD->show();
}
