#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFontDialog>
#include <QIcon>
#include <QColorDialog>
#include <QFileDialog>
#include <QFileIconProvider>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QFontDialog FontDialog;
    QColorDialog ColorDialog;
    QFileDialog FileDialog;
    QFileIconProvider FileIconProvider;
    QList<QUrl> BackUrls;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_preview_clicked();

    void on_pushButton_edit_font_clicked();

    void on_pushButton_setcolour_clicked();

    void on_checkBox_x_toggled(bool checked);

    void on_checkBox_y_toggled(bool checked);

    void on_pushButton_getback_clicked();

    void on_pushButton_get_folder_clicked();

    void on_spinBox_red_valueChanged(int arg1);

    void on_spinBox_green_valueChanged(int arg1);

    void on_spinBox_blue_valueChanged(int arg1);

    void on_pushButton_names_clicked();

    void on_pushButton_generate_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
