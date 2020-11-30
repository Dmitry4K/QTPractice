#ifndef RULEDSURFACEBYCARDINALSPLINE_H
#define RULEDSURFACEBYCARDINALSPLINE_H
#include "glabstractpainting.h"
#include "cardinalsplineclass.h"
#include <QObject>
#include <QVector>
class RuledSurfaceByCardinalSpline : public GLAbstractPainting

{
    Q_OBJECT
    QVector<QVector3D> bufferFLinePoints;
    QVector<QVector3D> bufferSLinePoints;
    float precision = 10;
    void paintLine(CardinalSplineClass& line, QVector<QVector3D>& buffer, float pres);
public:
    CardinalSplineClass fLine;
    CardinalSplineClass sLine;
    void setPrecision(float p);
    float getPrecision();
    RuledSurfaceByCardinalSpline();
    void paint() override;
public slots:
    void recievePrecision(int p);
    void acceptChanges();
signals:
    void surfaceChanged();
};

#endif // RULEDSURFACEBYCARDINALSPLINE_H
