#include "widget3d.h"
#include "mainwidget.h"
#include <QApplication>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWidget* mainWidget = new MainWidget();
    mainWidget->show();
    return a.exec();
}
