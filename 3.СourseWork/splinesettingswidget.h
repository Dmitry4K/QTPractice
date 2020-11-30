#ifndef SPLINESETTINGSWIDGET_H
#define SPLINESETTINGSWIDGET_H

#include "pointfieldwidget.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QScrollArea>
#include "cardinalsplineclass.h"
class SplineSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    CardinalSplineClass* spline = nullptr;
    QVBoxLayout* vLayout = nullptr;
    QScrollArea* saPoints = new QScrollArea;
    QVBoxLayout* vLayoutPoints = new QVBoxLayout;
    QPushButton* plusButton = new QPushButton;
    QPushButton* minusButton = new QPushButton;
    PointsWidget* pw = new PointsWidget(spline);
    SplineSettingsWidget(CardinalSplineClass* s);
public slots:
    void onClickPlusButton();
    void onClickMinusButton();
};

#endif // SPLINESETTINGSWIDGET_H
