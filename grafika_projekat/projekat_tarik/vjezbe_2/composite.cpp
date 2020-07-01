#include <GL/glut.h>

void drawCoordinates() {
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
  /*x*/
  glVertex2f(-100.0, 0.0);
  glVertex2f(100.0, 0.0);
  /*y*/
  glVertex2f(0.0, -100.0);
  glVertex2f(0.0, 100.0);
  glEnd();
}

void drawPolygon() {
  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.0);
  glVertex2f(25.0, 0.0);
  glVertex2f(25.0, 25.0);
  glVertex2f(0.0, 25.0);
  glEnd();
}

void transformationOrder() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  drawCoordinates();
  // red polygon
  glColor3f(1.0, 0.0, 0.0);
  glScalef(-1.0, 1.0, 1.0);
  glRotatef(45, 0.0, 0.0, 1.0);
  glTranslatef(50.0, 0.0, 0.0);
  drawPolygon();

  glLoadIdentity();
  // green polygon
  glColor3f(0.0, 1.0, 0.0);
  glTranslatef(50.0, 0.0, 0.0);
  glRotatef(45, 0.0, 0.0, 1.0);
  glScalef(-1.0, 1.0, 1.0);
  drawPolygon();
  glFlush();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  drawCoordinates();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 0.0);

  glTranslatef(25.0, 25.0, 0.0);
  drawPolygon();

  glPushMatrix();

     glTranslatef(-75.0, 0.0, 0.0);
     drawPolygon();
   
     glColor3f(0.0, 1.0, 0.0);
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   
     glPushMatrix();
        glRotatef(45.0, 0.0, 0.0, 1.0);
        drawPolygon();
     glPopMatrix();
   
     glScalef(2.0, 2.0, 1.0);
     glTranslatef(0.0, -50, 0.0);
     drawPolygon();

  glPopMatrix();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 0.0);
  glTranslatef(0.0, -100.0, 0.0);
  drawPolygon();

  glFlush();
}

void init() {
  /*set coordinate system*/
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutCreateWindow("Composite");
  glutInitWindowSize(800, 800);
  init();
  glutDisplayFunc(transformationOrder);
  glutDisplayFunc(display);
  glutMainLoop();
}
