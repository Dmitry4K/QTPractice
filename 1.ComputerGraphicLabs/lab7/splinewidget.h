#ifndef SPLINEWIDGET_H
#define SPLINEWIDGET_H

#include"splineclass.h"
#include<QMouseEvent>
#include<QWidget>
#include<QObject>


class SplineWidget : public QWidget
{
    Q_OBJECT
private:
public:
    SplineClass spline;
    bool isDrawSubLines = true;
    QList<SplinePoint>::iterator selectedPoint;
    bool isSelected = false;
    bool isRailSelected = false;
    int splineWidth = 3;
    SplineWidget(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void keyPressEvent(QKeyEvent* e) override;
    QPointF cordsOnCenter(const QPointF& p);

    QPointF toNormalCord(const QPointF& p);
public slots:
    void rePaint();
    void rePaint(int p);
    void rePaintSubLineSettings(int state);
    void rePaintAndSetSplineWidth(int width);
};

#endif // SPLINEWIDGET_H
