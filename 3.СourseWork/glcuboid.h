#ifndef GLCUBOID_H
#define GLCUBOID_H

#include "glabstractpainting.h"

class GLCuboid : public GLAbstractPainting
{
private:
    float height, width, length;
    int pres = 20;
public:
    GLCuboid(float h, float w, float l);
    void setPrecision(int p);
    void paint() override;
};

#endif // GLCUBOID_H
