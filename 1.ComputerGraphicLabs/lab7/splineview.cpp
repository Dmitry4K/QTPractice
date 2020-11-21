#include "splineview.h"
#include <QLabel>
SplineView::SplineView()
{
    vLayout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout();
    pSlider = new QSlider(Qt::Horizontal);
    isSubLinesWathched = new QCheckBox();
    lineWidth = new QSpinBox();
    splw = new SplineWidget(this);
    vLayout->addLayout(hLayout);
        hLayout->addWidget(pSlider);
        hLayout->addWidget(new QLabel("Precision"));
        hLayout->addWidget(isSubLinesWathched);
        hLayout->addWidget(lineWidth);
        hLayout->addWidget(new QLabel("Line"));
    vLayout->addWidget(splw,1);

    pSlider->setSingleStep(1);
    pSlider->setRange(1, 60);
    pSlider->setValue(splw->spline.getPresicion());

    isSubLinesWathched->setChecked(true);
    isSubLinesWathched->setText("Additional lines");

    lineWidth->setSingleStep(1);
    lineWidth->setRange(1,9);
    lineWidth->setValue(splw->splineWidth);
    QObject::connect(pSlider, SIGNAL(valueChanged(int)), splw, SLOT(rePaint(int)));
    QObject::connect(isSubLinesWathched, SIGNAL(stateChanged(int)), splw, SLOT(rePaintSubLineSettings(int)));
    QObject::connect(lineWidth, SIGNAL(valueChanged(int)), splw, SLOT(rePaintAndSetSplineWidth(int)));
}

void SplineView::keyPressEvent(QKeyEvent* e){
    splw->keyPressEvent(e);
}

