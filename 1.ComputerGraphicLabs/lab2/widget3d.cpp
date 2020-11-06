#include "widget3d.h"
#include "cuboidclass.h"
#include "transform.h"
#include "sphereclass.h"
#include <QtMath>
Widget3D::Widget3D(QWidget *parent)
    : QWidget(parent), scene(this)
{
     setMinimumSize(320, 240);
     scene.viewPoint.setZ(-500);
     scene.addFigure(new CuboidClass(80, 120, 100));
     //scene.addFigure(new SphereClass(70, 100));
     scene.setDefSizes(320, 240);
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
