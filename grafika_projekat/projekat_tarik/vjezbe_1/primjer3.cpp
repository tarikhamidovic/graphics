#include <GL/glut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // glBegin(GL_LINES);
  // glBegin(GL_LINE_STRIP);
  // glBegin(GL_LINE_LOOP);
  // glBegin(GL_TRIANGLES);
  // glBegin(GL_TRIANGLE_STRIP);
  // glBegin(GL_TRIANGLE_FAN);
  // glBegin(GL_QUADS);
  // glBegin(GL_QUAD_STRIP);
  glBegin(GL_POLYGON);

  glColor3f(1.0, 0.0, 1.0);
  glVertex2f(-0.5, -0.25);
  glVertex2f(-0.5, -0.5);
  // glVertex2f(-0.7, 0.25);

  glColor3f(0.0, 1.0, 0.0);
  glVertex2f(0.25, -0.25);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.35, 0.65);

  glEnd();
  glBegin(GL_POLYGON);

  glColor3f(1.0, 0.0, 1.0);
  glVertex2f(-0.5, -0.25);
  glVertex2f(-0.5, -0.5);
  // glVertex2f(-0.7, 0.25);

  glColor3f(0.0, 1.0, 0.0);
  glVertex2f(0.25, -0.25);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.35, 0.65);

  glEnd();

  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1000, 800);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Moj prozor");

  glutDisplayFunc(display);

  glutMainLoop();
  return 0;
}
