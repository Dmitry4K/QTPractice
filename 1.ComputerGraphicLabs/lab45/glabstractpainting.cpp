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
