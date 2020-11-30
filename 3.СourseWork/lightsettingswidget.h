#ifndef LIGHTSETTINGSWIDGET_H
#define LIGHTSETTINGSWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QColorDialog>
const int MAX_VALUE_SLIDER_LW = 1000;
class LightSettingsWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    QHBoxLayout* hLayout = new QHBoxLayout();
    bool isAmbient = false;
    bool isSpecular = false;
    bool isDiffuse = false;
public:
    QColor ambient = Qt::white;
    QColor specular = Qt::white;
    QColor diffuse = Qt::white;
    QColorDialog* cD = new QColorDialog();
    QSlider* sliderPositionX = new QSlider(Qt::Horizontal);
    QSlider* sliderPositionY = new QSlider(Qt::Horizontal);
    QSlider* sliderPositionZ = new QSlider(Qt::Horizontal);
    QPushButton* pushButtonAmbient = new QPushButton("Ambient:"+cD->selectedColor().name());
    QPushButton* pushButtonDiffuse = new QPushButton("Diffuse:"+cD->selectedColor().name());
    QPushButton* pushButtonSpecular = new QPushButton("Specular:"+cD->selectedColor().name());

    LightSettingsWidget();

public slots:
    void getColorDialogA();
    void getColorDialogS();
    void getColorDialogD();
    void lightChanged(const QColor&);
signals:
    void lightColorChanged();
};

#endif // LIGHTSETTINGSWIDGET_H
