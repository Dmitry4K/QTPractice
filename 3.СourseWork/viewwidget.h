#ifndef VIEWIDGET_H
#define VIEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSlider>
#include <QPushButton>
#include "glwidget.h"
#include "glcuboid.h"
#include "glsphere.h"
#include "lightsettingswidget.h"
#include "ruledsurfacebycardinalspline.h"
#include "surfacesettingswidget.h"
const int MAX_VALUE_SLIDER = 1000;

class ViewWidget : public QWidget
{
    Q_OBJECT
private:
    RuledSurfaceByCardinalSpline surface;
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    QVBoxLayout* vLayout = new QVBoxLayout();
    QHBoxLayout* hLayoutRotations = new QHBoxLayout();
    SurfaceSettingsWidget ssw;
public slots:
    void configChanged(int);
    void configChanged();
    void showLightSettings();
public:
    LightSettingsWidget* lsw = new LightSettingsWidget();
    ViewWidget();
    ~ViewWidget();
    GlWidget* glw = new GlWidget;
    QCheckBox* isHidingBack = new QCheckBox();
    QCheckBox* isLigthing = new QCheckBox();
    QSlider* sliderRotX = new QSlider(Qt::Vertical);
    QSlider* sliderRotY = new QSlider(Qt::Vertical);
    QSlider* sliderRotZ = new QSlider(Qt::Vertical);
    QPushButton* ligthSettings = new QPushButton();
};

#endif // VIEWIDGET_H
