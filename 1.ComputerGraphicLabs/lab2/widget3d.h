#ifndef WIDGET_H
#define WIDGET_H
#include "scenemodifier.h"
#include <QWidget>

class Widget3D : public QWidget
{
    Q_OBJECT

public:
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
};
#endif // WIDGET_H
