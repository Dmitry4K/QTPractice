#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GL_GLEXT_PROTOTYPES
#include<QtOpenGL>
#include"glfigureengine.h"

class GlWidget : public QGLWidget
{
public:
    GLFigureEngine Engine;
    GlWidget(QWidget* parent = nullptr);
    void initializeGL() override;
    void resizeGL(int nWidth, int nHeight) override;
    void paintGL() override;
};

#endif // GLWIDGET_H
