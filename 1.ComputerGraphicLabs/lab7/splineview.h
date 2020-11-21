#ifndef SPLINEVIEW_H
#define SPLINEVIEW_H

#include "splinewidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QCheckBox>
#include <QSpinBox>
class SplineView : public QWidget
{
    Q_OBJECT
public:
    QHBoxLayout* hLayout;
    SplineWidget* splw;
    QVBoxLayout* vLayout;
    QSlider* pSlider;
    QCheckBox* isSubLinesWathched;
    QSpinBox* lineWidth;
    void keyPressEvent(QKeyEvent* e) override;
    SplineView();
};

#endif // SPLINEVIEW_H
