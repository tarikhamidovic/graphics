#include <GL/glut.h>

void drawTriangle(const float* c1, const float* c2, const float* c3, float* xy1,
                  float* xy2, float* xy3) {
  glColor3fv(c1);
  glVertex2fv(xy1);
  glColor3fv(c2);
  glVertex2fv(xy2);
  glColor3fv(c3);
  glVertex2fv(xy3);
}

void modifyCoordinates(float* xy1, float* xy2, float* xy3) {
  *xy1 += 0.05;
  *(xy1 + 1) += 0.05;

  *xy2 -= 0.05;
  *(xy2 + 1) += 0.05;

  *(xy3 + 1) -= 0.1;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_TRIANGLES);
  // glBegin(GL_POLYGON);
  // glBegin(GL_TRIANGLE_FAN);

  static const float c1[] = {1, 0, 0};
  static const float c2[] = {0, 1, 0};
  static const float c3[] = {0, 0, 1};

  float xy1[] = {-0.6, -0.75};
  float xy2[] = {0.6, -0.75};
  float xy3[] = {0, 0.75};

  drawTriangle(c1, c2, c3, xy1, xy2, xy3);

  modifyCoordinates(xy1, xy2, xy3);
  drawTriangle(c3, c1, c2, xy1, xy2, xy3);

  modifyCoordinates(xy1, xy2, xy3);
  drawTriangle(c2, c3, c1, xy1, xy2, xy3);

  modifyCoordinates(xy1, xy2, xy3);
  drawTriangle(c1, c2, c3, xy1, xy2, xy3);

  modifyCoordinates(xy1, xy2, xy3);
  drawTriangle(c3, c1, c2, xy1, xy2, xy3);

  modifyCoordinates(xy1, xy2, xy3);
  drawTriangle(c2, c3, c1, xy1, xy2, xy3);

  modifyCoordinates(xy1, xy2, xy3);
  drawTriangle(c1, c2, c3, xy1, xy2, xy3);

  glEnd();

  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(1200, 800);
  glutCreateWindow("Guess");

  glutDisplayFunc(display);

  glutMainLoop();
}
