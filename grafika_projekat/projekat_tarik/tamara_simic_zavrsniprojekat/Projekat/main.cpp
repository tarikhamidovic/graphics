#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdexcept>
#include"image.h"

#define PI 3.1415926
#define MAX_LENGTH 1000
#define SUN_RADIUS 13
#define EARTH_RADIUS 4
#define MOON_RADIUS 2

void makeEnvironmentWithLight();
void makeCamera();
void drawSun();

GLuint earthTextureId;
GLuint sunTextureId;
GLuint moonTextureId;
bool texture=false;

GLuint loadTexture(Image* image){
  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixel);
  return textureId;
}

void drawSun(){
  glPushMatrix();
  glEnable(GL_LIGHT1);
  if(texture){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,sunTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GLUquadricObj *quad = gluNewQuadric();
    gluQuadricTexture(quad,GLU_TRUE);
    gluSphere(quad,SUN_RADIUS,30,30);
    glDisable(GL_TEXTURE_2D);
  }
  else{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.650,0.650,0.650);
    GLUquadricObj *quad = gluNewQuadric();
    gluSphere(quad,SUN_RADIUS,30,30);
  }

  glDisable(GL_LIGHT1);
  glPopMatrix();

}

double MoonRevolutionW = 2.0*PI/273;
double MoonRevolutionTheta = 0;

void drawMoon(){
  glPushMatrix();
  double x = cos(MoonRevolutionTheta);
  double y = sin(MoonRevolutionTheta);
  glTranslatef(10*x,10*y,0);
  if(texture){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,moonTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GLUquadricObj *quad = gluNewQuadric();
    gluQuadricTexture(quad,GLU_TRUE);
    gluSphere(quad,MOON_RADIUS,30,30);
  }
  else{
    GLUquadricObj *quad = gluNewQuadric();
    glColor3f(0.192,0.192,0.192);
    gluSphere(quad,MOON_RADIUS,30,30);
  }

  glPopMatrix();
}

void MoonUpdate(){
  drawMoon();
  MoonRevolutionTheta += MoonRevolutionW;
}

double EarthRevolutionW = 2.0*PI/3560;
double EarthRevolutionTheta = 0;

double EarthRotationW = 30;
double EarthRotationTheta = 0;

void drawEarth(){
  double x = cos(EarthRevolutionTheta);
  double y = sin(EarthRevolutionTheta);
  glPushMatrix();
  glTranslatef(40*x,40*y,0);
  //glRotatef(EarthRotationTheta,0,0,1);
  if(texture){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,earthTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GLUquadricObj *quad = gluNewQuadric();
    gluQuadricTexture(quad,GLU_TRUE);
    gluSphere(quad,EARTH_RADIUS,30,30);
    glDisable(GL_TEXTURE_2D);
  }
  else{
    GLUquadricObj *quad = gluNewQuadric();
    glColor3f(0,0,1);
    gluSphere(quad,EARTH_RADIUS,30,30);
  }

  glPopMatrix();
  glPushMatrix();
  glTranslatef(40*x,40*y,0);
  MoonUpdate();
  glPopMatrix();
}

void EarthUpdate(){
  drawEarth();
  EarthRevolutionTheta += EarthRevolutionW;
  EarthRotationTheta += EarthRotationW;
}

void init(){
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  Image* image = loadBMP("earth.bmp");
  earthTextureId = loadTexture(image);
  delete image;

  image = loadBMP("sun.bmp");
  sunTextureId = loadTexture(image);
  delete image;

  image = loadBMP("moon.bmp");
  moonTextureId = loadTexture(image);
  delete image;

  glEnable(GL_NORMALIZE);
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  makeEnvironmentWithLight();

  makeCamera();

  drawSun();
  EarthUpdate();

  glutSwapBuffers();
  glFlush();
}

void makeEnvironmentWithLight(){
  GLfloat ambient[4] = {0.2,0.2,0.2,1};
  GLfloat diffuse[4] = {1,1,1,1};
  GLfloat position[4] = {0,0,0,1};
  GLfloat specular[4] = { 1, 1, 1, 1};
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
  glLightfv(GL_LIGHT0,GL_POSITION,position);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

  GLfloat ambient1[4] = {5,5,5,1};
  GLfloat diffuse1[4] = {1,1,1,1};
  GLfloat position1[4] = {0,0,0,1};
  glLightfv(GL_LIGHT1,GL_AMBIENT,ambient1);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse1);
  glLightfv(GL_LIGHT1,GL_POSITION,position1);
}

void makeCamera(){
  int w = glutGet((GLenum)GLUT_WINDOW_WIDTH);
  int h = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
  glViewport(0,0,w,h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60,1.0*w/h,1.0,MAX_LENGTH);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(50,50,20,0,0,0,0,0,2);

}


void timer(int e){
  glutPostRedisplay();
  glutTimerFunc(30,timer,0);
}

void mouse(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON){
    EarthRotationW*=2;
    EarthRevolutionW*=2;
    MoonRevolutionW*=2;
  }
  if(button==GLUT_LEFT_BUTTON){
    EarthRotationW/=2;
    EarthRevolutionW/=2;
    MoonRevolutionW/=2;
  }
}

void kbd(unsigned char key, int x, int y){
  switch(key){
    case 27:
      exit(0);
      break;
    case 'n':
    case 'N':
      glDisable(GL_LIGHTING);
      glDisable(GL_LIGHT0);
      texture=false;
      break;
    case 'l':
    case 'L':
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      break;
    case 't':
    case 'T':
      texture=true;
      break;
  }
}

int main(int argc, char **argv){
  glutInit(&argc,argv);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Sunce, Zemlja i Mjesec");
  glutInitDisplayMode(GL_RGB | GL_DEPTH | GL_DOUBLE);

  glutDisplayFunc(display);
  glutTimerFunc(30,timer,0);
  glutMouseFunc(mouse);
  glutKeyboardFunc(kbd);

  init();
  glutMainLoop();
  return 0;
}
