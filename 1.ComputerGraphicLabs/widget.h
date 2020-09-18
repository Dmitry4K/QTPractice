#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRect>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QRect button;
    QRect cur_button;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_verticalSlider_sliderMoved(int position);

    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
