#ifndef WIDJETLIGHTSETTINGS_H
#define WIDJETLIGHTSETTINGS_H

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QColorDialog>
#include <QPushButton>

const int MAX_VALUE_SLIDER = 1000;
class WidjetLightSettings : public QWidget
{
    Q_OBJECT
public:
    QColorDialog* cD = new QColorDialog();
    QSlider* sliderX = new QSlider(Qt::Horizontal);
    QSlider* sliderY = new QSlider(Qt::Horizontal);
    QSlider* sliderZ = new QSlider(Qt::Horizontal);
    QSlider* sliderRadius = new QSlider(Qt::Horizontal);
    QSlider* sliderIntensity = new QSlider(Qt::Horizontal);
    QSlider* sliderK = new QSlider(Qt::Horizontal);
    QPushButton* lightButton = new QPushButton();
    WidjetLightSettings();
public slots:
    void getColorDialog();
};

#endif // WIDJETLIGHTSETTINGS_H
