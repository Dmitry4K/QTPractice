#include "widget3d.h"
#include "cuboidclass.h"
#include "transform.h"
#include "sphereclass.h"
#include <QtMath>
Widget3D::Widget3D(QWidget *parent)
    : QWidget(parent), scene(this)
{
     setMinimumSize(320, 240);
     lightSettings = new WidjetLightSettings();
     sphere = new SphereClass(70 ,100);
     sphere->Color = Qt::yellow;
     scene.viewPoint.setZ(-500);
     scene.addFigure(sphere);
     scene.setDefSizes(minimumSize().width(), minimumSize().height());

     LightPoint light(QVector4D(1.0,1.0,1.0,1.0));

     light.setColor(lightSettings->cD->currentColor());
     scene.setLightPoint(light);

     QObject::connect(lightSettings->sliderX, SIGNAL(valueChanged(int)),
                       this, SLOT(lightChanged(int)));
     QObject::connect(lightSettings->sliderY, SIGNAL(valueChanged(int)),
                       this, SLOT(lightChanged(int)));
     QObject::connect(lightSettings->sliderZ, SIGNAL(valueChanged(int)),
                       this, SLOT(lightChanged(int)));
     QObject::connect(lightSettings->sliderRadius, SIGNAL(valueChanged(int)),
                       this, SLOT(lightChanged(int)));
     QObject::connect(lightSettings->sliderIntensity, SIGNAL(valueChanged(int)),
                       this, SLOT(lightChanged(int)));
     QObject::connect(lightSettings->cD, SIGNAL(colorSelected(const QColor&))
                      , this, SLOT(lightChanged(const QColor&)));
     QObject::connect(lightSettings->sliderK, SIGNAL(valueChanged(int)),
                      this, SLOT(lightChanged(int)));
}

Widget3D::~Widget3D(){
}
void Widget3D::paintEvent(QPaintEvent*){
    scene.paint();
}
void Widget3D::rotationX(int angle){
    scene.transformer.setRotationX(float(angle) * M_PI / 180.0);
    update();
}
void Widget3D::rotationY(int angle){
    scene.transformer.setRotationY(float(angle)* M_PI / 180.0);
    update();
}
void Widget3D::rotationZ(int angle){
    scene.transformer.setRotationZ(float(angle)* M_PI / 180.0);
    update();
}
void Widget3D::showingChange(int isIzometric){
    scene.transformer.isIzometric = isIzometric;
    update();
}

void Widget3D::hidingChange(int state){
    scene.setHidingBackSide(state > 0);
    update();
}

void Widget3D::changePrecision(int precision){
    sphere->setPrecision(precision);
    update();
}

void Widget3D::relesedButtonLightSettings(){
    lightSettings->show();
}
float f1(float v){
    return (v>0 ? ((abs(v) - 500.0f)/500.0f) : -((abs(v) + 500.0f)/500.0f));
}
float f2(float v){
    return v/MAX_VALUE_SLIDER;
}
float f3(float v){
    return (v/MAX_VALUE_SLIDER);
}
void Widget3D::lightChanged(int){
    LightPoint newLight({f1((float)lightSettings->sliderX->value()),
                          f1((float)lightSettings->sliderY->value()),
                          f1((float)lightSettings->sliderZ->value()), 1.0f});
    newLight.setRadius(f2((float)lightSettings->sliderRadius->value()));
    newLight.setIntensity(f3((float)lightSettings->sliderIntensity->value()));
    newLight.setColor(lightSettings->cD->currentColor());
    newLight.setK(f3((float)lightSettings->sliderK->value()));
    scene.setLightPoint(newLight);
    lightSettings->lightButton->setText(newLight.getColor().name());
    update();
}

void Widget3D::lightChanged(const QColor&){
    lightChanged(0);
}

void Widget3D::lightEnabling(int state){
    scene.setEnableLight(state>0);
    update();
}

