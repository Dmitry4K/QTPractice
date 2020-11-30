#include "glsphere.h"
#include <QVector3D>
GLSphere::GLSphere(float r, float p) :
    radius(r),
    precision(p)
{

}

float GLSphere::getRadius() const{
    return radius;
}
void GLSphere::setRadius(float r){
    radius = r;
}
float GLSphere::getPrecision() const{
    return precision;
}
void GLSphere::setPrecision(float p){
    precision = p;
}

void GLSphere::paint(){
    QVector<QVector3D>* arc_prev = new QVector<QVector3D>;
    QVector<QVector3D>* arc_this = new QVector<QVector3D>;
    QVector<QVector3D>* arc_first = new QVector<QVector3D>;
    bool save_first = false;
    float ring_length = 2.0f * M_PI;
    float step = ring_length / precision;
    QColor color = (getMode() == FRAME ? getFrameColor() : getMaterialColor());
    float red = color.red();
    float blue = color.blue();
    float green = color.green();
    float cosGma;
    float sinGma;
    float cosPhi;
    float sinPhi;
    QVector3D cur_point(0.0f, 0.0f, 0.0f);
    for(float gma = 0.0f; gma <= 2.0f * M_PI;gma += step){
        int i = 0 ;
        cosGma = cosf(gma);
        sinGma = sinf(gma);
        for(float phi = -M_PI_2;phi< M_PI_2; phi += step){
            cosPhi = cosf(phi);
            sinPhi = sin(phi);
            cur_point.setX(radius * cosGma * cosPhi);
            cur_point.setY(radius * sinPhi);
            cur_point.setZ(radius * sinGma * cosPhi);
            if(arc_prev->size()){
                if(i < (arc_prev->size() - 1) && i > 0){
                    glBegin(GL_POLYGON);
                    glColor3f(red, green, blue);
                    glVertex3f(  cur_point.x(),cur_point.y(), cur_point.z() );
                    glVertex3f(  arc_prev->at(i).x(),arc_prev->at(i).y(),arc_prev->at(i).z());
                    glVertex3f(  arc_prev->at(i+1).x(),arc_prev->at(i+1).y(),arc_prev->at(i+1).z());
                    glEnd();
                    glBegin(GL_POLYGON);
                    glColor3f(red, green, blue);
                    glVertex3f(  arc_this->at(i-1).x(),arc_this->at(i-1).y(), arc_this->at(i-1).z() );
                    glVertex3f(  arc_prev->at(i).x(),arc_prev->at(i).y(),arc_prev->at(i).z());
                    glVertex3f(  cur_point.x(),cur_point.y(),cur_point.z());
                    glEnd();
                 //polygons->push_back(new Polygon3D(cur_point,arc_prev->at(i+1),arc_prev->at(i)));
                 //polygons->push_back(new Polygon3D(arc_this->at(i-1),cur_point,arc_prev->at(i)));
                }
            }
            arc_this->push_back(cur_point);
            ++i;
        }
        float phi = M_PI_2;
        float cosPhi = cosf(phi);
        float sinPhi = sin(phi);
        cur_point.setX(radius * cosGma * cosPhi);
        cur_point.setY(radius * sinPhi);
        cur_point.setZ(radius * sinGma * cosPhi);
        //if(arc_prev->size()){
          //  polygons->push_back(new Polygon3D(cur_point,arc_prev->at((i+1 == arc_prev->size() ? 0 : i+1)),arc_prev->at(i)));
        //}
        arc_this->push_back(cur_point);
        if(!save_first){
            save_first = true;
            *arc_first = *arc_this;
        }
        qSwap(arc_prev, arc_this);
        arc_this->clear();
    }
    for(int i = 0;i<arc_first->size()-1;++i){
        if(i < arc_prev->size() - 1 && i > 0){glBegin(getMode());
            glBegin(GL_POLYGON);
            glColor3f(red, green, blue);
            glVertex3f(  arc_first->at(i).x(),arc_first->at(i).y(), arc_first->at(i).z() );
            glVertex3f(  arc_prev->at(i).x(),arc_prev->at(i).y(),arc_prev->at(i).z());
            glVertex3f(  arc_prev->at(i+1).x(),arc_prev->at(i+1).y(),arc_prev->at(i+1).z());
            glEnd();
            glBegin(GL_POLYGON);
            glColor3f(red, green, blue);
            glVertex3f(  arc_first->at(i-1).x(),arc_first->at(i-1).y(), arc_first->at(i-1).z() );
            glVertex3f(  arc_prev->at(i).x(),arc_prev->at(i).y(),arc_prev->at(i).z());
            glVertex3f(  arc_first->at(i).x(),arc_first->at(i).y(),arc_first->at(i).z());
            glEnd();
            //polygons->push_back(new Polygon3D(arc_first->at(i),arc_prev->at(i+1),arc_prev->at(i)));
            //polygons->push_back(new Polygon3D(arc_first->at(i-1),arc_first->at(i),arc_prev->at(i)));
        }
    }
    delete arc_prev;
    delete arc_this;
}
