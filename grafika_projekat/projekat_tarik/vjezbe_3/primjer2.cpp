#include <GL/glut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // unutrasnji i vanjski radius, broj uzduznih i poprecnih presjeka
  glutWireTorus(0.5, 3, 15, 30);

  glBegin(GL_LINES);

  // x
  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(10, 0, 0);

  // y
  glColor3f(0, 1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 10, 0);

  // z
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 10);

  glEnd();

  glFlush();
}

void init() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //   glOrtho(-5, 5, -5, 5, -10, 10);
  glOrtho(-15, 15, -15, 15, -10, 10);
  //   glOrtho(-5, 5, -5, 5, 10, 20);

  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(900, 675);
  glutCreateWindow("Primjer2");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}