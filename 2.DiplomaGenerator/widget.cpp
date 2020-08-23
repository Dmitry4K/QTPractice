#include "widget.h"
#include "ui_widget.h"
#include "script.h"

#include<QMessageBox>
#include<QDesktopServices>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton_getback->setIcon(FileIconProvider.icon(QFileIconProvider::Folder));
    ui->pushButton_get_folder->setIcon(FileIconProvider.icon(QFileIconProvider::Folder));
    ui->pushButton_names->setIcon(FileIconProvider.icon(QFileIconProvider::Folder));
    ColorDialog.setCurrentColor(Qt::black);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_preview_clicked()
{
    auto background = ui->lineEdit_backimage->text();
    auto folder = ui->lineEdit_folder->text();
    auto text = ui->lineEdit_text->text();
    auto x = ui->spinBox_x->value();
    auto y = ui->spinBox_y->value();
    auto color = ColorDialog.currentColor();
    auto font = FontDialog.currentFont();
    if(background.isEmpty()){
        QMessageBox er;
        er.setText("Choose background image!");
        er.exec();
        return;
    }
    if(folder.isEmpty()){
        QMessageBox er;
        er.setText("Choose folder!");
        er.exec();
        return;
    }
    QString result_name = "preview";
    int error = 0;
    if(!GenerateDiploma(BackUrls, text, x, y, color, font,folder, result_name, &error)){
        QString er("error : ");
        er += erToString(error);
        ui->label_preview->setText(er);
    }
    else{
        QPixmap img(folder + '/'+result_name+".jpg");
        ui->label_preview->setPixmap(img);
    }
}

void Widget::on_pushButton_edit_font_clicked()
{
    auto& leFont = ui->lineEdit_font;
    auto& leSize = ui->lineEdit_size;
    auto& leStyle = ui->lineEdit_style;
    bool ok;
    auto Font = FontDialog.getFont(&ok);
    if(ok){
        FontDialog.setCurrentFont(Font);
        leFont->setText(Font.family());
        leSize->setText(QString::number(Font.pointSize()));
        leStyle->setText(Font.styleName());
    }
}

void Widget::on_pushButton_setcolour_clicked()
{
    auto Color = ColorDialog.getColor();
    if(Color.isValid()){
        ColorDialog.setCurrentColor(Color);
        ui->spinBox_red->setValue(Color.red());
        ui->spinBox_blue->setValue(Color.blue());
        ui->spinBox_green->setValue(Color.green());
    }
}

void Widget::on_checkBox_x_toggled(bool checked)
{
    ui->spinBox_x->setEnabled(!checked);
    ui->spinBox_x->setValue(0);
}

void Widget::on_checkBox_y_toggled(bool checked)
{
    ui->spinBox_y->setEnabled(!checked);
    ui->spinBox_y->setValue(0);
}

void Widget::on_pushButton_getback_clicked()
{
    auto Urls = FileDialog.getOpenFileUrls(this, tr("Select Images"), QUrl(), tr("Images (*.png *.xpm *.jpg)"));
    if(!Urls.isEmpty()){
        QString urls = Urls.at(0).toString(QUrl::RemoveScheme|QUrl::PreferLocalFile);
        for(int i = 1;i<Urls.size();++i){
               urls += ' ' + Urls.at(i).toString(QUrl::RemoveScheme|QUrl::PreferLocalFile);
        }
        ui->lineEdit_backimage->setText(urls);
        BackUrls = Urls;
    }
}

void Widget::on_pushButton_get_folder_clicked()
{
    //FileDialog.setFileMode(QFileDialog::Directory);
    auto Url = FileDialog.getExistingDirectoryUrl();
    if(!Url.isEmpty()){
        ui->lineEdit_folder->setText(Url.toString(QUrl::RemoveScheme|QUrl::PreferLocalFile));
    }
}

void Widget::on_spinBox_red_valueChanged(int arg1)
{
    auto Color = ColorDialog.currentColor();
    Color.setRed(arg1);
    ColorDialog.setCurrentColor(Color);
}

void Widget::on_spinBox_green_valueChanged(int arg1)
{
    auto Color = ColorDialog.currentColor();
    Color.setGreen(arg1);
    ColorDialog.setCurrentColor(Color);
}

void Widget::on_spinBox_blue_valueChanged(int arg1)
{
    auto Color = ColorDialog.currentColor();
    Color.setBlue(arg1);
    ColorDialog.setCurrentColor(Color);
}

void Widget::on_pushButton_names_clicked()
{
    auto Url = FileDialog.getOpenFileUrl(this, tr("Select \"txt\" file"), QUrl(), tr("Files (*.txt)"));
    if(!Url.isEmpty()){
        ui->lineEdit_names->setText(Url.toString(QUrl::RemoveScheme|QUrl::PreferLocalFile));
    }
}

void Widget::on_pushButton_generate_clicked()
{
    ui->pushButton_preview->setEnabled(false);
    ui->pushButton_generate->setEnabled(false);
    auto folder = ui->lineEdit_folder->text();
    auto x = ui->spinBox_x->value();
    auto y = ui->spinBox_y->value();
    auto color = ColorDialog.currentColor();
    auto font = FontDialog.currentFont();
    auto names = ui->lineEdit_names->text();

    if(BackUrls.isEmpty()){
        QMessageBox er;
        er.setText("Choose background image!");
        er.exec();
        ui->pushButton_preview->setEnabled(true);
        ui->pushButton_generate->setEnabled(true);
        return;
    }
    if(folder.isEmpty()){
        QMessageBox er;
        er.setText("Choose folder!");
        er.exec();
        ui->pushButton_preview->setEnabled(true);
        ui->pushButton_generate->setEnabled(true);
        return;
    }
    if(names.isEmpty()){
        QMessageBox er;
        er.setText("Choose txt file!");
        er.exec();
        ui->pushButton_preview->setEnabled(true);
        ui->pushButton_generate->setEnabled(true);
        return;
    }

    QString result_name = "diplom_";
    int error = 0;
    int count = 0;
    QFile file(names);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    int i = 0;
    QString text;
    while(getLine(file, text)){
        if(GenerateDiploma(BackUrls, text, x, y, color, font,folder, result_name+QString::number(i), &error)){
            ++count;
        }
        text.clear();
        ++i;
    }
    QMessageBox msg;
    msg.setText(QString("Done/All : %1/%2").arg(count).arg(i));
    msg.exec();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folder));
    ui->pushButton_preview->setEnabled(true);
    ui->pushButton_generate->setEnabled(true);
    ui->lineEdit_folder->clear();
}
