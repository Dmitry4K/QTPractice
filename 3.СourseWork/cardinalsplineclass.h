#ifndef CARDINALSPLINECLASS_H
#define CARDINALSPLINECLASS_H

#include"polynom.h"
#include<QList>
#include<QVector3D>
#include<QObject>
class CardinalSplineClass : public QObject
{
    Q_OBJECT
private:
    class CardinalSplineSegmentClass {
    public:
        Polynom xPolynom;
        Polynom yPolynom;
        Polynom zPolynom;
        QVector3D calculatePoint(float t){
            return QVector3D(xPolynom.calculatePolynom(t), yPolynom.calculatePolynom(t), zPolynom.calculatePolynom(t));
        }
    };

    QList<QVector3D> points;
    QList<CardinalSplineSegmentClass> segments;
    float k = 0;
    void calculatePolynom(Polynom& fP, Polynom& sP, float p1, float p2);
    void preCalculation();
    void postCalculation();
    void calculateLastPolynom(Polynom& pol, float pl, float pr);
public:
    QList<CardinalSplineSegmentClass>& getSegments();
    QList<QVector3D>& getPoints();
    void destroy();
    CardinalSplineClass();
    void setK(float nk);
    float getK();
    void addPoint(const QVector3D p);
    void calculate();
    bool isValid();
public slots:
    void acceptPointChanges(int index, QVector3D p);
    void acceptNewK(int);
    void acceptNewPoint(QVector3D);
    void removeLast();
signals:
    void splineChanged();
};

#endif // CARDINALSPLINECLASS_H
