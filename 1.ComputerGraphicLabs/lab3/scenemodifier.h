#ifndef SCENEMODIFIER_H
#define SCENEMODIFIER_H

#include <QWidget>
#include <QVector>

#include "abstractpaintitng3d.h"
#include "transformer.h"
#include "lightpoint.h"

class SceneModifier
{
private:
    LightPoint lightPoint = LightPoint(QVector4D(1.0,1.0,1.0,1.0));
    int default_width = 0;
    int default_height = 0;
    QWidget* canvas = nullptr;
    bool hidingBack = true;
    QVector<AbstractPaintitng3D*> figures;
    bool enableLight = false;
public:
    void setEnableLight(bool);
    void setLightPoint(const LightPoint& );
    void setDefSizes(int w, int h);
    void setHidingBackSide(bool);
    void removeLight();
    Transformer transformer;
    QVector4D viewPoint;
    void paint();
    SceneModifier(QWidget*);
    void addFigure(AbstractPaintitng3D*);
    virtual ~SceneModifier();
};


#endif // SCENEMODIFIER_H
