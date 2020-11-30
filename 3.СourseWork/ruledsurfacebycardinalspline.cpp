#include "ruledsurfacebycardinalspline.h"

RuledSurfaceByCardinalSpline::RuledSurfaceByCardinalSpline()
{
    QObject::connect(&fLine, SIGNAL(splineChanged()), this, SLOT(acceptChanges()));
    QObject::connect(&sLine, SIGNAL(splineChanged()), this, SLOT(acceptChanges()));
    setFrameColor(Qt::black);
    setMaterialColor(Qt::blue);
}

void RuledSurfaceByCardinalSpline::setPrecision(float p){
    if(precision != p){
        precision = p;
        emit surfaceChanged();
    }
}
float RuledSurfaceByCardinalSpline::getPrecision(){
    return precision;
}

void RuledSurfaceByCardinalSpline::paint(){
    if(fLine.isValid() && sLine.isValid()){
        fLine.calculate();
        sLine.calculate();
        if(fLine.getSegments().size() > sLine.getSegments().size()){
            paintLine(fLine, bufferFLinePoints, precision);
            paintLine(sLine, bufferSLinePoints, precision * (float)fLine.getSegments().size()/(float)sLine.getSegments().size());

        } else{
            paintLine(fLine, bufferFLinePoints, precision * (float)sLine.getSegments().size()/(float)fLine.getSegments().size());
            paintLine(sLine, bufferSLinePoints, precision);
        }
        while(bufferFLinePoints.size() < bufferSLinePoints.size())
            bufferFLinePoints.push_back(fLine.getSegments().back().calculatePoint(1));
        while(bufferFLinePoints.size() > bufferSLinePoints.size())
            bufferSLinePoints.push_back(sLine.getSegments().back().calculatePoint(1));
        for(int i = 0;i<bufferFLinePoints.size()-1;++i){
            /*
            addPolygon(bufferFLinePoints[i], bufferFLinePoints[i+1], bufferSLinePoints[i]);
            addPolygon(bufferFLinePoints[i+1], bufferSLinePoints[i+1], bufferSLinePoints[i]);
            */
            addPolygon(bufferFLinePoints[i], bufferSLinePoints[i],bufferFLinePoints[i+1]);
            addPolygon(bufferFLinePoints[i+1],bufferSLinePoints[i], bufferSLinePoints[i+1]);
        }
    }
}

void RuledSurfaceByCardinalSpline::acceptChanges(){
    emit surfaceChanged();
}

void RuledSurfaceByCardinalSpline::paintLine(CardinalSplineClass& line, QVector<QVector3D>& buffer, float pres){
    buffer.clear();
    auto& segments = line.getSegments();
    float step = 1/pres;
    QVector3D p;
    for(int i = 0;i<segments.size(); ++i){
        for(float s = 0; s < 1; s+= step){
            p = segments[i].calculatePoint(s);
            buffer.push_back(p);
        }
    }
    p = segments.back().calculatePoint(1);
    buffer.push_back(p);
}

void RuledSurfaceByCardinalSpline::recievePrecision(int p){
    setPrecision(p);
}
