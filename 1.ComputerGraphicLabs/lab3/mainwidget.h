#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "widget3d.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    Widget3D* view = new Widget3D(nullptr);
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QHBoxLayout* slidersHBox = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QSlider *angleXS = new QSlider(Qt::Vertical);
    QSlider *angleYS = new QSlider(Qt::Vertical);
    QSlider *angleZS = new QSlider(Qt::Vertical);
    QSlider* precisS = new QSlider(Qt::Horizontal);
    QPushButton* lightingSettingsButton = new QPushButton();
    QCheckBox* izometricCB = new QCheckBox();
    QCheckBox* hidebackCB = new QCheckBox();
    QCheckBox* enableLight = new QCheckBox();
    QLabel* rotationLbl = new QLabel();
signals:

};

#endif // MAINWIDGET_H
