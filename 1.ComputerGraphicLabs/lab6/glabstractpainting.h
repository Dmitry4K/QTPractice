#ifndef GLABSTRACTPAINTING_H
#define GLABSTRACTPAINTING_H

#include<QtOpenGL>

const GLenum FRAME = GL_LINE;
const GLenum MATERIAL = GL_FILL;
class GLAbstractPainting : public QObject
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
    QColor getColor();
    GLenum getMode() const;
    GLAbstractPainting();
    void addPolygon(const QVector3D& f, const QVector3D& s, const QVector3D& t);
    void addPolygon(const QVector3D& f, const QVector3D& s, const QVector3D& t, QColor c);
    virtual void paint() = 0;
    virtual void animate(int){};
    virtual ~GLAbstractPainting();
};

#endif // GLABSTRACPAINTING_H
