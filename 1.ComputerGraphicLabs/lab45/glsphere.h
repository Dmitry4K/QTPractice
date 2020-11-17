#ifndef GLSPHERE_H
#define GLSPHERE_H

#include "glabstractpainting.h"
class GLSphere : public GLAbstractPainting
{
    float radius, precision;
public:
    GLSphere(float r, float p);
    float getRadius() const;
    void setRadius(float r);
    float getPrecision() const;
    void setPrecision(float p);
    void paint() override;
};

#endif // GLSPHERE_H
