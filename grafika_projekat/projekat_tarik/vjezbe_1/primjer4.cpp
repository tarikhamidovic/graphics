#include <GL/glut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  glBegin(GL_POLYGON);

  glColor3f(0.0, 0.9, 0.7);
  glVertex2f(-0.5, -0.25);
  glVertex2f(-0.5, 0.5);
  glVertex2f(0.25, -0.25);

  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  glBegin(GL_POLYGON);

  glColor3f(1.0, 0.5, 0.7);
  glVertex2f(-0.5, -0.25);
  glVertex2f(-0.5, 0.5);
  glVertex2f(0.25, -0.25);

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
