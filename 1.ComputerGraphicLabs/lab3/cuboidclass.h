#ifndef CUBOIDCLASS_H
#define CUBOIDCLASS_H

#include"abstractpaintitng3d.h"
#include"rectpolygon3d.h"

class CuboidClass : public AbstractPaintitng3D
{
private:
    QVector4D points[8];
    float length, width, height;
public:
    CuboidClass(float l, float w, float h);
    //void calculateLines() override;
    void calculatePolygons() override;
    void setLength(float l);
    void setWidth(float w);
    void setHeight(float h);
    void setSize(float l, float w, float h);
};

#endif // PARALLELEPIPEDCLASS_H
