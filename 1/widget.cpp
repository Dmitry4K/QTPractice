#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    cur_button = button = ui->pushButton->geometry();
    ui->verticalSlider->setMaximum(ui->verticalSlider->geometry().height());
    ui->horizontalSlider->setMaximum(ui->horizontalSlider->geometry().width());
    ui->pushButton->setText(QString("%1 x %2").arg(ui->pushButton->x()).arg(ui->pushButton->y()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    ui->pushButton->setGeometry(button);
    ui->verticalSlider->setSliderPosition(0);
    ui->horizontalSlider->setSliderPosition(0);
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    cur_button.setX(button.x()+position);
    cur_button.setHeight(button.height());
    cur_button.setWidth(button.width());
    ui->pushButton->setGeometry(cur_button);
    ui->pushButton->setText(QString("%1 x %2").arg(ui->pushButton->x()).arg(ui->pushButton->y()));
}

void Widget::on_verticalSlider_sliderMoved(int position)
{
    cur_button.setY(button.y()+position);
    cur_button.setWidth(button.width());
    cur_button.setHeight(button.height());
    ui->pushButton->setGeometry(cur_button);
    ui->pushButton->setText(QString("%1 x %2").arg(ui->pushButton->x()).arg(ui->pushButton->y()));
}

void Widget::on_verticalSlider_valueChanged(int value)
{
    on_verticalSlider_sliderMoved(value);
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    on_horizontalSlider_sliderMoved(value);
}
