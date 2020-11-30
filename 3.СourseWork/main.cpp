#include "glwidget.h"

#include <QApplication>
#include <viewwidget.h>
#include "splinesettingswidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewWidget view;
    view.show();
    return a.exec();
}
