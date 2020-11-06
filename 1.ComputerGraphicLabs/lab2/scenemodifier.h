#ifndef SCENEMODIFIER_H
#define SCENEMODIFIER_H

#include <QWidget>
#include <QVector>

#include "abstractpaintitng3d.h"
#include "transformer.h"

class SceneModifier
{
private:
    int default_width = 0;
    int default_height = 0;
    QWidget* canvas = nullptr;
    bool hidingBack = true;
    QVector<AbstractPaintitng3D*> figures;
public:
    void setDefSizes(int w, int h);
    void setHidingBackSide(bool);
    Transformer transformer;
    QVector4D viewPoint;
    void paint();
    SceneModifier(QWidget*);
    void addFigure(AbstractPaintitng3D*);
    virtual ~SceneModifier();
};


#endif // SCENEMODIFIER_H
