#include <GL/glut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);

  // centar
  glTranslatef(0.0, 0.0, 3.0);
  glPushMatrix();
  glRotatef(45, 2, 2, 2);
  glutWireTetrahedron();
  glPopMatrix();

  // gornji desni
  glTranslatef(2.0, 2.0, -1.0);
  glutWireIcosahedron();

  // gornji lijevi
  glTranslatef(-4.0, 0.0, -1.0);
  glutWireCone(1, 3, 15, 15);

  // donji lijevi
  glTranslatef(0.0, -4.0, -1.0);
  glutWireCube(2.0);

  // donji desni
  glTranslatef(4.0, 0.0, -1.0);
  glutWireSphere(0.8, 15, 15);
  glFlush();
}

void switchToOrtho() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5, 5, -5, 5, -10, 10);
}

void switchToFrustum() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-2, 2, -2, 2, 3.0, 10);
}

void kbd(unsigned char key, int x, int y) {
  switch (key) {
  case 27:
    exit(0);
    break;
  case 'o':
    switchToOrtho();
    break;
  case 'f':
    switchToFrustum();
    break;
  }
  glutPostRedisplay();
}

void reshape(GLint w, GLint h) { glViewport(0, 0, w, h); }

void init() {
  glColor3f(0.4, 0.0, 1.0);
  switchToOrtho();
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(700, 700);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Primjer3");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(kbd);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
