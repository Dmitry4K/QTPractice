#include "splinewidget.h"
#include <QPainter>
#include <QKeyEvent>

//subfunction ==============================
QPointF subLineFunction(const QPointF& p){
    return QPointF(p.x()+POINT_RADIUS/2, p.y()+POINT_RADIUS/2);
}

QPointF SplineWidget::cordsOnCenter(const QPointF& p){
    return QPointF(p.x() - width()/2, p.y() - height()/2);
}

QPointF SplineWidget::toNormalCord(const QPointF& p){
    return QPointF(p.x() + width()/2, p.y() + height()/2);
}
int centrizePointCord(int cord){
    return cord - POINT_RADIUS/2;
}
QPoint centrizePointCord(const QPoint& cord){
    return QPoint(centrizePointCord(cord.x()), centrizePointCord(cord.y()));
}
QPointF centrizePointCord(const QPointF& cord){
    return QPointF(centrizePointCord(cord.x()), centrizePointCord(cord.y()));
}
//==========================================

SplineWidget::SplineWidget(QWidget* p) : QWidget(p)
{
    setMinimumSize(480,480);
    QObject::connect(&spline, SIGNAL(lineChanged()), this, SLOT(rePaint()));
}

void SplineWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    auto& points = spline.getPoints();
    if(spline.isValid()){
        QPen pen(Qt::red);
        pen.setWidth(splineWidth);
        painter.setPen(pen);
        spline.calculate();
        float step = 1/(float)spline.getPresicion();
        QPointF prev = points[0];
        for(float i = step;i < 1.0f;i += step ){
            QPointF next = spline.fSegment.claculatePoint(i);
            painter.drawLine(subLineFunction(toNormalCord(prev)), subLineFunction(toNormalCord(next)));
            prev = next;
        }
        painter.drawLine(subLineFunction(toNormalCord(prev)), subLineFunction(toNormalCord(spline.fSegment.claculatePoint(1))));
        prev = points[1];
        for(float i = step;i < 1.0f;i += step ){
            QPointF next = spline.sSegment.claculatePoint(i);
            painter.drawLine(subLineFunction(toNormalCord(prev)), subLineFunction(toNormalCord(next)));
            prev = next;
        }
        painter.drawLine(subLineFunction(toNormalCord(prev)), subLineFunction(toNormalCord(spline.sSegment.claculatePoint(1))));
    }
    painter.setBrush(Qt::SolidPattern);
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    if(isDrawSubLines){
        for(int i = 1;i<points.size();++i){
            painter.drawLine(subLineFunction(toNormalCord(points[i-1])),subLineFunction(toNormalCord(points[i])));
        }
        for(auto el = points.begin(); el != points.end(); ++el){
            if(!el->isRailNull()){
                painter.setPen(Qt::SolidLine);
                painter.drawLine(subLineFunction(toNormalCord(el->toPoint())),subLineFunction(toNormalCord(el->toPoint() + el->getRail())));
                QPointF rect = toNormalCord(el->toPoint()+el->getRail());
                painter.setBrush(QColor{240,240,240});
                painter.drawRect(rect.x(), rect.y(),POINT_RADIUS,POINT_RADIUS);
                painter.setBrush(Qt::black);
            }
            QPointF elips = toNormalCord(QPointF(el->x(), el->y()));
            painter.drawEllipse(elips.x(), elips.y(), POINT_RADIUS, POINT_RADIUS);
        }
    }
}

void SplineWidget::mousePressEvent(QMouseEvent* e){
    if(e->buttons()  == Qt::LeftButton){
        if(!spline.add(QPointF(centrizePointCord(cordsOnCenter(e->pos()))))){
            selectedPoint = spline.findPointOrRail(centrizePointCord(cordsOnCenter(e->pos())));
            if(selectedPoint != spline.getPoints().end()){
                isSelected = true;
                if(!isCatch(selectedPoint->getRail().x()+selectedPoint->x(),
                           selectedPoint->getRail().y()+selectedPoint->y(),
                           centrizePointCord(cordsOnCenter(e->pos())).x(),
                           centrizePointCord(cordsOnCenter(e->pos())).y())){
                    isRailSelected = false;
                } else {
                    isRailSelected = true;
                }
            }
        }
    }
}

void SplineWidget::mouseMoveEvent(QMouseEvent* e){
    if(e->buttons() == Qt::LeftButton && isSelected){
        if(isRailSelected && !selectedPoint->isRailNull()){
            selectedPoint->setRail(centrizePointCord(cordsOnCenter(e->pos())));
        } else {
            selectedPoint->setX(centrizePointCord(cordsOnCenter(e->pos())).x());
            selectedPoint->setY(centrizePointCord(cordsOnCenter(e->pos())).y());
        }
        emit spline.lineChanged();
    }
}

void SplineWidget::mouseReleaseEvent(QMouseEvent* e){
    if(spline.getPoints().size() == 1){
        spline.getPoints()[0].setRail(centrizePointCord(cordsOnCenter(e->pos())));
        emit spline.lineChanged();
    }
    if(spline.getPoints().size() == 3 && spline.getPoints()[2].isRailNull()){
        spline.getPoints()[2].setRail(centrizePointCord(cordsOnCenter(e->pos())));
        emit spline.lineChanged();
    }
    isSelected = false;
       // spline.add(QPointF(centrizePointCord(cordsOnCenter(e->pos()))));
}

void SplineWidget::keyPressEvent(QKeyEvent* e){
    if(e->key() == Qt::Key_Delete ){
        spline.clear();
    }
}

void SplineWidget::rePaint(){
    update();
}

void SplineWidget::rePaint(int p){
    spline.setPresicion(p);
    rePaint();
}

void SplineWidget::rePaintSubLineSettings(int state){
    isDrawSubLines = state;
    rePaint();
}

void SplineWidget::rePaintAndSetSplineWidth(int width){
    splineWidth = width;
    rePaint();
}
