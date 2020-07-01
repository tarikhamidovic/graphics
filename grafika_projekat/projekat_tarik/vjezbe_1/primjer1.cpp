#include <GL/glut.h>
#include <iostream>

void display() {
  std::cout << "display" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT);
  
  glPointSize(8.0);
  glEnable(GL_POINT_SMOOTH);

  glBegin(GL_POINTS);

  glColor3f(1.0, 0.5, 0.7);
  glVertex2f(-0.5, -0.25);
  glVertex2f(-0.5, 0.5);
  glColor3f(0.0, 0.5, 0.7);
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

  glClearColor(0.15, 0.15, 0.15, 0);
  glutDisplayFunc(display);

  glutMainLoop();
  return 0;
}
