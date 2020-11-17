#include "glwidget.h"

GlWidget::GlWidget(QWidget* parent) : QGLWidget(parent) {
    setMinimumHeight(480);
    setMinimumWidth(480);
}
void GlWidget::initializeGL(){
       qglClearColor(QColor(240,240,240));
       glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
       // glShadeModel(GL_FLAT); // отключает режим сглаживания цветов


}
void GlWidget::resizeGL(int nW, int nH){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nW, (GLint)nH);
}
void GlWidget::paintGL(){
    Engine.setProjection(width(), height());
    Engine.paint();
}
