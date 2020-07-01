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
  // kamera gleda pod 60 stepeni, omjer je 4:3 i sve blize od 1 i dalje
  // od 40 jedinica od kamere nece biti prikazano
  gluPerspective(60, 4 / 3.0, 1, 40);
  //   gluPerspective(-60, 4 / 3.0, 1, 40);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // pozicioniramo kameru u (4,6,5), koja gleda u (0,0,0)
  //   gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
  gluLookAt(4, 6, 5, 0, 0, 0, 0, 0, 1);
  //   gluLookAt(4, 6, -5, 0, 0, 0, 0, 1, 0);
  //   gluLookAt(4, 6, 25, 0, 0, 0, 0, 1, 0);
  //   gluLookAt(4, 6, 5, 0, 0, -10, 0, 1, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(900, 675);
  glutCreateWindow("Primjer1");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}