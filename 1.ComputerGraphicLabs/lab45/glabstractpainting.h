#ifndef GLABSTRACTPAINTING_H
#define GLABSTRACTPAINTING_H

#include<QtOpenGL>

const GLenum FRAME = GL_LINE;
const GLenum MATERIAL = GL_FILL;
class GLAbstractPainting
{
private:
    GLenum mode = FRAME;
    QColor colorFrame = Qt::black;
    QColor colorMaterial = Qt::yellow;
public:
    void setFrameColor(QColor c);
    QColor getFrameColor() const;
    void setMaterialColor(QColor c);
    QColor getMaterialColor() const;
    void setMode(GLenum m);
    GLenum getMode() const;
    GLAbstractPainting();
    virtual void paint() = 0;
    virtual ~GLAbstractPainting();
};

#endif // GLABSTRACPAINTING_H
