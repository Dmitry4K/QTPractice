#include "glabstractpainting.h"

GLAbstractPainting::GLAbstractPainting()
{

}
GLAbstractPainting::~GLAbstractPainting()
{

}

void GLAbstractPainting::setMode(GLenum m){
    mode = m;
}

GLenum GLAbstractPainting::getMode() const{
    return mode;
}

void GLAbstractPainting::setFrameColor(QColor c){
    colorFrame = c;
}
QColor GLAbstractPainting::getFrameColor() const{
    return colorFrame;
}

void GLAbstractPainting::setMaterialColor(QColor c){
    colorMaterial = c;
}

QColor GLAbstractPainting::getMaterialColor() const{
    return colorMaterial;
}

void GLAbstractPainting::addPolygon(const QVector3D& f, const QVector3D& s, const QVector3D& t){
    auto c = getColor();
    glBegin(GL_POLYGON);
    glColor3f(c.redF(), c.greenF(), c.blueF());
    glVertex3f(  f.x(), f.y(), f.z());
    glVertex3f(  s.x(), s.y(), s.z());
    glVertex3f(  t.x(), t.y(), t.z());
    glEnd();
}

void addPolygon(const QVector3D& f, const QVector3D& s, const QVector3D& t, QColor c){
    glBegin(GL_POLYGON);
    glColor3f(c.redF(), c.greenF(), c.blueF());
    glVertex3f(  f.x(), f.y(), f.z());
    glVertex3f(  s.x(), s.y(), s.z());
    glVertex3f(  t.x(), t.y(), t.z());
    glEnd();
}

QColor GLAbstractPainting::getColor(){
    return getMode() == FRAME ? getFrameColor() : getMaterialColor();
}
