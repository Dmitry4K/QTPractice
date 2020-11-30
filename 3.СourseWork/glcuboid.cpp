#include "glcuboid.h"
#include <QtOpenGL>
GLCuboid::GLCuboid(float h, float w, float l):
    height(h),
    width(w),
    length(l)
{
}

void GLCuboid::paint(){
    glBegin(GL_POLYGON);//GL_POLYGON
    float a = height/2;
    float b = width/2;
    float c = length/2;
    QColor color = (getMode() == FRAME ? getFrameColor() : getMaterialColor());
    float red = color.red();
    float blue = color.blue();
    float green = color.green();
    glColor3f(red, green, blue);
    glVertex3f( -a, -b, -c);       // P1
    glVertex3f( -a,  b, -c);       // P2
    glVertex3f(  a,  b, -c);       // P3
    glVertex3f(  a, -b, -c);
    glEnd();
    // Белая сторона — ЗАДНЯЯ
    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);
    glVertex3f(  a, -b, c );
    glVertex3f(  a,  b, c );
    glVertex3f( -a,  b, c );
    glVertex3f( -a, -b, c );
    glEnd();

    // Фиолетовая сторона — ПРАВАЯ
    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);
    glVertex3f( a, -b, -c );
    glVertex3f( a,  b, -c );
    glVertex3f( a,  b,  c );
    glVertex3f( a, -b,  c );
    glEnd();

    // Зеленая сторона — ЛЕВАЯ
    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);
    glVertex3f( -a, -b,  c );
    glVertex3f( -a,  b,  c );
    glVertex3f( -a,  b, -c );
    glVertex3f( -a, -b, -c );
    glEnd();

    // Синяя сторона — ВЕРХНЯЯ
    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);
    glVertex3f(  a,  b,  c );
    glVertex3f(  a,  b, -c );
    glVertex3f( -a,  b, -c );
    glVertex3f( -a,  b,  c );
    glEnd();

    // Красная сторона — НИЖНЯЯ
    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);
    glVertex3f(  a, -b, -c );
    glVertex3f(  a, -b,  c );
    glVertex3f( -a, -b,  c );
    glVertex3f( -a, -b, -c );
    glEnd();
    glFlush();
}


void GLCuboid::setPrecision(int p){
    pres = p;
}
