#include"script.h"
#include<QImage>
#include<QPainter>
#include<QRect>
#include<QTextDecoder>
#include<QTextCodec>
#include <QRandomGenerator>
#include <QTime>

bool GenerateDiploma(const QList<QUrl>& backgrounds, const QString& text, int x, int y, const QColor& color, const QFont& font,const QString& folder, const QString& result_name, int* error){
    QRandomGenerator rg;
    rg.seed(QTime::currentTime().msec());
    QImage image(backgrounds.at(rg.bounded(backgrounds.size())).toString(QUrl::RemoveScheme|QUrl::PreferLocalFile));
    if(image.isNull()){
        *error = IMAGE_OPENENING_ERROR;
        return false;
    }
    QPainter p;
    if (!p.begin(&image)){
        *error = PAINTER_BEGINNIG_ERROR;
        return false;
    }

    p.setPen(color);
    p.setFont(font);
    QRect rect = image.rect();
    rect.setX(x);
    rect.setY(y);
    p.drawText(rect, Qt::AlignCenter, text);
    p.end();

    if(!image.save(folder + '/' + result_name+".jpg" ,"JPG")){
        *error = IMAGE_SAVING_ERROR;
        return false;
    }
    *error = NO_ERROR;
    return true;
}

QString erToString(int er){
    if(er == IMAGE_OPENENING_ERROR){
        return "image openening error";
    }
    if(er == PAINTER_BEGINNIG_ERROR){
        return "painter begining error";
    }
    if(er == IMAGE_SAVING_ERROR){
        return "image saving error";
    }
    return "no error";
}

bool getLine(QFile& file, QString& str){
    char* data;
    int max_size = 100;
    data = new char[max_size];
    bool result;
    qint64 size;
    if((size = file.readLine(data, max_size))!=-1){
        if (data[size-1] == '\n'){
            data[size-1] = '\0';
        }
        result = true;
          str = QString(data);
    }
    else{
        result = false;
    }
    return result;
}
