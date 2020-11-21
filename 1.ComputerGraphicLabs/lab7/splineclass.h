#ifndef SPLINECLASS_H
#define SPLINECLASS_H
#include<QList>
#include<QPointF>
#include<QObject>
#include<QPainter>
const int POINT_RADIUS = 10;

class Polynom{
public:
    float calculatePolynom(float t){
        return a * t * t * t + b * t * t + c * t + d;
    }
    float a;
    float b;
    float c;
    float d;
};

bool isCatch(int x, int y, int px, int py);
class SplinePoint : public QPointF{

    QPointF rail = {0, 0};
    bool israilnull = true;
public:
    QPointF getRail(){
        return rail;
    }
    QPointF toPoint() {
        return (QPointF)(*this);
    }
    void setRail(const QPointF& p){
        israilnull = false;
        rail = p - toPoint();
    }
    void delRail(){
        israilnull = true;
    }
    bool isRailNull(){
        return israilnull;
    }
};

class SplineClass : public QObject
{
    Q_OBJECT
private:
    QList<SplinePoint> points;
    class SplineSegment{
    public:
        Polynom xPolynom;
        Polynom yPolynom;
        QPointF claculatePoint(float t){
            return QPointF(xPolynom.calculatePolynom(t), yPolynom.calculatePolynom(t));
        }
    };
    int presicion = 50;
public:
    void calculatePolynoms(Polynom& fP, Polynom& sP, int p0, int p1, int p2, int r0, int r2);
    void calculate();
    SplineSegment fSegment;
    SplineSegment sSegment;
    SplineClass();
    QList<SplinePoint>& getPoints();
    bool add(int x, int y);
    bool add(const QPointF&);
    void clear();
    bool isValid();
    QList<SplinePoint>::iterator findPoint(int x, int y);
    QList<SplinePoint>::iterator findPoint(const QPointF& p);
    QList<SplinePoint>::iterator findPointOrRail(const QPointF& p);
    QList<SplinePoint>::iterator findPointOrRail(int x, int y);
    int getPresicion();
    void setPresicion(int presiscion);
public slots:
signals:
    void lineChanged();
};

#endif // SPLINECLASS_H
