#ifndef SURFACESETTINGSWIDGET_H
#define SURFACESETTINGSWIDGET_H

#include"splinesettingswidget.h"
#include<QSpinBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
#include<QSlider>

class SurfaceSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    RuledSurfaceByCardinalSpline* surf;
    QVBoxLayout vLayout;
    QHBoxLayout hLayout;
    QHBoxLayout hLayoutPrecision;
    QHBoxLayout hLayoutK;
    QSlider sbK;
    QSlider sbPrecision;
    SplineSettingsWidget fLineWidget;
    SplineSettingsWidget sLineWidget;

    SurfaceSettingsWidget(RuledSurfaceByCardinalSpline* s);
};

#endif // SURFACESETTINGSWIDGET_H
