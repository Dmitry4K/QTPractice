#include "widget3d.h"

#include <QApplication>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QWidget* mainWidget = new QWidget();
    Widget3D* view = new Widget3D(nullptr);
    QHBoxLayout *hLayout = new QHBoxLayout(mainWidget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(view, 1);
    hLayout->addLayout(vLayout);

    QHBoxLayout* slidersHBox = new QHBoxLayout();
    slidersHBox->setAlignment(Qt::AlignTop);
    QSlider *angleXS = new QSlider(Qt::Vertical);
    QSlider *angleYS = new QSlider(Qt::Vertical);
    QSlider *angleZS = new QSlider(Qt::Vertical);

    angleXS->setInvertedAppearance(true);
    angleYS->setInvertedAppearance(true);
    angleZS->setInvertedAppearance(true);
    angleXS->setRange(0,360);
    angleYS->setRange(0,360);
    angleZS->setRange(0,360);

    angleXS->setSingleStep(1);
    angleYS->setSingleStep(1);
    angleZS->setSingleStep(1);

    QCheckBox* izometricCB = new QCheckBox();
    izometricCB->setText("izometric");
    izometricCB->setChecked(true);
    vLayout->addWidget(izometricCB);
    QCheckBox* hidebackCB = new QCheckBox();
    hidebackCB->setText("hide back");
    hidebackCB->setChecked(true);
    vLayout->addWidget(hidebackCB);
    QLabel* rotationLbl = new QLabel();
    rotationLbl->setText("Rotation angles");
    vLayout->addWidget(rotationLbl);
    slidersHBox->addWidget(angleXS);
    slidersHBox->addWidget(angleYS);
    slidersHBox->addWidget(angleZS);
    vLayout->addLayout(slidersHBox);

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
    mainWidget->show();
    return a.exec();
}
