#include <GL/glut.h>

#define sunRaduis 0.4
#define earthRaduis 0.06
#define moonRaduis 0.016

GLfloat rotationSpeed = 0.15;
GLfloat daysInYear = 365;
GLfloat year = 0.0;
GLfloat day = 0.0;
GLfloat moonAroundEarth = 0.0;
GLfloat moonItsSelf = 0.0;
GLfloat earthOrbitRadius = 1.0;
GLfloat moonOrbitRadius = 0.1;
GLfloat moonAroundEarthRate = 2 * rotationSpeed;
GLfloat moonRotationItselfRate = 5.0 * rotationSpeed;
GLfloat dayRate = 5.0 * rotationSpeed;
GLfloat yearRate = daysInYear / 360.0 * dayRate * rotationSpeed;

int a = 0;

void drawSolarSystem() {
  glPushMatrix();
  gluLookAt(0.0, 0.0, -4.0, 0.0, 0.0, 1.0, 0.0, -3.0, 0.0);

  glColor3f(1.0, 1.0, 0.2);
  glutSolidSphere(sunRaduis, 50, 50);
  glPushMatrix();

  glRotatef(year, 0.0, 1.0, 0.0);
  glTranslatef(earthOrbitRadius, 0.0, 0.0);
  glRotatef(-year, 0.0, 1.0, 0.0);
  glPushMatrix();
  glRotatef(day, 0.25, 1.0, 0.0);
  glColor3f(0.385, 0.57, 0.19);
  glutSolidSphere(earthRaduis, 10, 10);

  glPopMatrix();
  glRotatef(moonAroundEarth, 0.0, 1.0, 0.0);
  glTranslatef(moonOrbitRadius, 0.0, 0.0);

  glRotatef(-moonAroundEarth, 0.0, 1.0, 0.0);
  glRotatef(moonItsSelf, 0.0, 1.0, 0.0);

  glColor3f(0.65, 0.65, 0.65);
  glutSolidSphere(moonRaduis, 8, 8);
  glPopMatrix();

  glPopMatrix();
}

void init() {
  glClearColor(0.0, 0.0, 0.1, 0.0);
  glClearDepth(10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void idle() {
  ++a;
  day += dayRate;
  year += yearRate;
  moonItsSelf += moonRotationItselfRate;
  moonAroundEarth += moonAroundEarthRate;
  glutPostRedisplay();
}

void display() {
  if (a == 500) {
    glutIdleFunc(NULL);
  }
  glClear(GL_COLOR_BUFFER_BIT);
  drawSolarSystem();
  glFlush();
  glutSwapBuffers();
}

void reshape(int x, int y) {
  glLoadIdentity();
  gluPerspective(40.0, (GLdouble)x / y, 0.5, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glViewport(0, 0, x, y);
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(700, 700);
  glutCreateWindow("Primjer4");
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}