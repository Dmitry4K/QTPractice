#include "glfigureengine.h"

GLFigureEngine::GLFigureEngine()
{
    timer.start(100);
}


void GLFigureEngine::paint(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    applyTransform();
    applyLight();
    for(auto* painting : paintings){
      if(!isAnimate){
        if(painting->getMode() == MATERIAL){
           prePaintSettings(painting);
           painting->paint();
        }
        if(painting->getMode() == FRAME){
            if(isHidingBack()){
               glLineWidth(1.5);
               prePaintSettings(painting);
               painting->paint();
               painting->setMode(MATERIAL);
               painting->setMaterialColor(QColor(240,240,240));
               prePaintSettings(painting);
               painting->paint();
               painting->setMode(FRAME);
           } else{
               glLineWidth(1);
               prePaintSettings(painting);
               painting->paint();
           }
         }
      } else {
          if(painting->getMode() == MATERIAL){
             prePaintSettings(painting);
             painting->animate(tick);
          }
          if(painting->getMode() == FRAME){
              if(isHidingBack()){
                 glLineWidth(1.5);
                 prePaintSettings(painting);
                 painting->animate(tick);
                 painting->setMode(MATERIAL);
                 painting->setMaterialColor(QColor(240,240,240));
                 prePaintSettings(painting);
                 painting->animate(tick);
                 painting->setMode(FRAME);
             } else{
                 glLineWidth(1);
                 prePaintSettings(painting);
                 painting->animate(tick);
             }
          }
          ++tick;
       }
    }
}

void GLFigureEngine::addFigure(GLAbstractPainting* f){
    paintings.push_back(f);
}
void GLFigureEngine::deleteFigures(){
    paintings.clear();
}
GLFigureEngine::~GLFigureEngine(){
}

void GLFigureEngine::setRotation(float x, float y, float z){
    setRotationX(x);
    setRotationY(y);
    setRotationZ(z);
}
float GLFigureEngine::getRotationX() const{
    return rotateX;
}
float GLFigureEngine::getRotationY() const{
    return rotateY;
}
float GLFigureEngine::getRotationZ() const{
    return rotateZ;
}
void GLFigureEngine::setRotationX(float a){
    rotateX = a;
}
void GLFigureEngine::setRotationY(float a){
    rotateY = a;
}
void GLFigureEngine::setRotationZ(float a){
    rotateZ = a;
}

void GLFigureEngine::applyTransform() const{
    glRotatef(rotateX, 1.0,0.0,0.0);
    glRotatef(rotateY, 0.0,1.0,0.0);
    glRotatef(rotateZ, 0.0,0.0,1.0);
    glScalef(scale, scale, scale);
}

void GLFigureEngine::disableBooleanProj(){
    isIzomteric = isOrtho = false;
}

void GLFigureEngine::setIzomtericProjection(){
    disableBooleanProj();
    isIzomteric = true;
}
void GLFigureEngine::setOrthoProjection(){
    disableBooleanProj();
    isOrtho = true;
}

bool GLFigureEngine::isIzomtericProjection(){
    return isIzomteric;
}
bool GLFigureEngine::isOrthoProjection(){
    return isOrtho;
}

void GLFigureEngine::setProjection(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float res = (float)w/(float)h;
    float hK = (res > 1 ? res : 1);
    float vK = (res < 1 ? 1/res : 1);
    if(isOrthoProjection())
        glOrtho(-1.0*hK, 1.0*hK, -1.0*vK, 1.0*vK, -10.0, 1.0);
    if(isIzomtericProjection()){
        glFrustum(-1.0*hK, 1.0*hK, -1.0*vK, 1.0*vK, 8, 10.0);
        glTranslatef(0.0,0.0,-9.0);
    }
}


void GLFigureEngine::prePaintSettings(GLAbstractPainting* figure){
    glPolygonMode(GL_FRONT_AND_BACK, figure->getMode());
}

bool GLFigureEngine::isHidingBack() const{
    return isHiddingBack;
}

void GLFigureEngine::setHidingBack(bool b){
    if(isHiddingBack != b){
        isHiddingBack = b;
    }
}

bool GLFigureEngine::isLightEnabled() const{
    return isLightEnab;
}
void GLFigureEngine::setLightEnabled(bool b){
    isLightEnab = b;
}

void GLFigureEngine::applyLight() const{
    if(isLightEnab){
        glEnable(GL_LIGHTING);
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        glEnable(GL_NORMALIZE);
        float red = light.diffuse.redF();
        float green = light.diffuse.greenF();
        float blue = light.diffuse.blueF();
        float light0_diffuse[] = {red, green, blue};
        red = light.specular.redF();
        green = light.specular.greenF();
        blue = light.specular.blueF();
        float light0_specular[] = {red, green, blue};
        float light0_direction[] = {light.direction.x(), light.direction.y(), light.direction.z(), 1.0};

        red = light.ambient.redF();
        green = light.ambient.greenF();
        blue = light.ambient.blueF();
        float light0_ambient[] = {red, green, blue};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);

        GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
    }
    else{
        glDisable(GL_LIGHTING);
    }
}

void GLFigureEngine::setAnimation(bool s){
    if(isAnimate != s){
        isAnimate = s;
        if(isAnimate){
            timer.start(20);
        }
        else{
            timer.stop();
        }
    }
}

bool GLFigureEngine::Animation(){
    return isAnimate;
}
