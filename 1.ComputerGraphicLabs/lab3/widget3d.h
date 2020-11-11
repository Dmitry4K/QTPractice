#ifndef WIDGET_H
#define WIDGET_H
#include "scenemodifier.h"
#include "abstractpaintitng3d.h"
#include <QWidget>
#include "sphereclass.h"
#include "widjetlightsettings.h"
class Widget3D : public QWidget
{
    Q_OBJECT
public:
    WidjetLightSettings* lightSettings = nullptr;
    SphereClass* sphere = nullptr;
    SceneModifier scene;
    Widget3D(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    ~Widget3D();
public slots:
    void rotationX(int angle);
    void rotationY(int angle);
    void rotationZ(int angle);
    void showingChange(int isIzometric);
    void hidingChange(int state);
    void changePrecision(int precision);
    void relesedButtonLightSettings();
    void lightEnabling(int state);
    void lightChanged(int);

    void lightChanged(const QColor&);
};
#endif // WIDGET_H
