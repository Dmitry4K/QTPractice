#include "surfacesettingswidget.h"
#include<QLabel>
SurfaceSettingsWidget::SurfaceSettingsWidget(RuledSurfaceByCardinalSpline* s) :
    vLayout(this),
    sbK(Qt::Horizontal),
    sbPrecision(Qt::Horizontal),
    fLineWidget(&s->fLine),
    sLineWidget(&s->sLine)
{
    sbPrecision.setValue(s->getPrecision());
    sbK.setValue(s->fLine.getK());
    sbK.setRange(-100, 100);
    vLayout.addLayout(&hLayoutPrecision);
        hLayoutPrecision.setAlignment(Qt::AlignLeft);
        hLayoutPrecision.addWidget(new QLabel("Precision"));
        hLayoutPrecision.addWidget(&sbPrecision);
            sbPrecision.setSingleStep(1);
            sbPrecision.setRange(0,100);
    vLayout.addLayout(&hLayoutK);
        hLayoutK.setAlignment(Qt::AlignLeft);
        hLayoutK.addWidget(new QLabel("Splines K"));
        hLayoutK.addWidget(&sbK);
    vLayout.addLayout(&hLayout);
        hLayout.addWidget(&fLineWidget);
        hLayout.addWidget(&sLineWidget);
    QObject::connect(&sbPrecision, SIGNAL(valueChanged(int)), s, SLOT(recievePrecision(int)));
    QObject::connect(&sbK, SIGNAL(valueChanged(int)), &s->sLine, SLOT(acceptNewK(int)));
    QObject::connect(&sbK, SIGNAL(valueChanged(int)), &s->fLine, SLOT(acceptNewK(int)));
}
