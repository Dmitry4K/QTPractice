#ifndef SPHERECLASS_H
#define SPHERECLASS_H

#include"abstractpaintitng3d.h"

class SphereClass : public AbstractPaintitng3D
{
    float precision = 0.01;
    float radius = 10.0;
public:
    void setPrecision(float p);
    void setRadius(float r);
    float getPrecision() const;
    float getRadius() const;
    SphereClass(float r, float p);
    void calculatePolygons() override;
};

#endif // SPHERECLASS_H
